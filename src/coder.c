/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 12:39:38 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/27 19:35:32 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//When compilation starts, it stores the current time
//in last_compile_start. This timestamp is used to determine burnout.
//Access is protected by data_mutex because the monitor
//reads it from another thread
static void	compile_phase(t_coder *coder)
{
	t_simulation	*simulation;

	simulation = coder->simulation;
	pthread_mutex_lock(&coder->data_mutex);
	coder->last_compile_start = get_current_time_ms();
	pthread_mutex_unlock(&coder->data_mutex);
	print_status(simulation, coder->id + 1, "is compiling");
	sleep_ms(simulation, simulation->config.time_to_compile);
	pthread_mutex_lock(&coder->data_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->data_mutex);
}

static void	debug_phase(t_coder *coder)
{
	print_status(coder->simulation, coder->id + 1, "is debugging");
	sleep_ms(coder->simulation, coder->simulation->config.time_to_debug);
}

static void	refactor_phase(t_coder *coder)
{
	print_status(coder->simulation, coder->id + 1, "is refactoring");
	sleep_ms(coder->simulation, coder->simulation->config.time_to_refactor);
}

static void *lone_coder_routine(t_coder *coder)
{
	print_status(coder->simulation, coder->id + 1, "has taken a dongle");
	return (NULL);
}

//the function that each thread executes
//It takes a void * argument and returns a void *.
//Cast the argument to t_coder *
//While the simulation has not stopped, the coder repeats the entire cycle.
//Once the stop flag is set, logging stops and waits end immediately,
//so the thread quickly exits the while loop and returns NULL.
void	*coder_routine(void *argument)
{
	t_coder	*coder;

	coder = (t_coder *)argument;
	if (coder->simulation->config.number_of_coders == 1)
	{
		return (lone_coder_routine(coder));
	}
	while (is_simulation_stopped(coder->simulation) == 0)
	{
		if (acquire_dongles(coder) == 0)
			break ;
		print_status(coder->simulation, coder->id + 1, "has taken a dongle");
		print_status(coder->simulation, coder->id + 1, "has taken a dongle");
		compile_phase(coder);
		release_dongles(coder);
		debug_phase(coder);
		refactor_phase(coder);
	}
	return (NULL);
}
