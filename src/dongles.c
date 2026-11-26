/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/26 16:52:42 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/26 17:21:34 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long long	get_request_key(t_coder *coder)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	if (simulation->config.use_edf == 1)
		return (coder->last_compile_start + simulation->config.time_to_burnout);
	simulation->next_ticket++;
	return (simulation->next_ticket);
}

//heand out the dongles, and only if someone received a pair, wake everyone
//up so they can check whether thay got theirs
static void	assign_and_notify(t_simulation *simulation)
{
	if (assign_ready_dongles(simulation) > 0)
		pthread_cond_broadcast(&simulation->dongle_condition);
}

static void	wait_for_change(t_simulation *simulation)
{
	long long		cooldown_end;
	struct timespec	wake_time;

	cooldown_end = get_next_cooldown_end(simulation);
	if (cooldown_end == 0)
		pthread_cond_wait(&simulation->dongle_condition,
			&simulation->dongle_mutex);
	else
	{
		wake_time.tv_sec = cooldown_end / 1000;
		wake_time.tv_nsec = (cooldown_end % 1000) * 1000000;
		pthread_cond_timedwait(&simulation->dongle_condition,
			&simulation->dongle_mutex, &wake_time);
	}

}

int	acquire_dongles(t_coder *coder)
{
	t_simulation	*simulation;
	t_heap_node		request;
	int				got_dongles;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->dongle_mutex);
	request.key = get_request_key(coder);
	request.coder_id = coder->id;
	coder->has_dongles = 0;
	heap_push(&simulation->waiting_queue, request);
	assign_and_notify(simulation);
	while (coder->has_dongles == 0
		&& is_simulation_stopped(simulation) == 0)
	{
		wait_for_change(simulation);
		assign_and_notify(simulation);
	}
	got_dongles = coder->has_dongles;
	pthread_mutex_unlock(&simulation->dongle_mutex);
	return (got_dongles);
}

void	release_dongles(t_coder *coder)
{
	t_simulation	*simulation;
	long long		available_time;
	int				right_index;

	simulation = coder->simulation;
	right_index = get_right_dongle_index(simulation, coder->id);
	available_time = get_current_time_ms();
	available_time = available_time + simulation->config.dongle_cooldown;
	pthread_mutex_lock(&simulation->dongle_mutex);
	simulation->dongles[coder->id].is_taken = 0;
	simulation->dongles[coder->id].available_at = available_time;
	simulation->dongles[right_index].is_taken = 0;
	simulation->dongles[right_index].available_at = available_time;
	assign_ready_dongles(simulation);
	pthread_cond_broadcast(&simulation->dongle_condition);
	pthread_mutex_unlock(&simulation->dongle_mutex);
}
