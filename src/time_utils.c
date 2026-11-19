/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 17:15:56 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/14 17:15:56 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Returns the current time in milliseconds
long long	get_current_time_ms(void)
{
	struct timeval	time_value;
	long long		seconds_in_ms;
	long long		microseconds_in_ms;

	gettimeofday(&time_value, NULL);
	seconds_in_ms = time_value.tv_sec * 1000;
	microseconds_in_ms = time_value.tv_usec / 1000;
	return (seconds_in_ms + microseconds_in_ms);
}

//Returns the number of milliseconds that have elapsed since a start time
long long	get_elapsed_time_ms(long long start_time)
{
	long long	current_time;

	current_time = get_current_time_ms();
	return (current_time - start_time);
}

//Wait for a number of milliseconds
//On each iteration it checks whether the simulation should stop.
//If so, it exits immediately with return
void	sleep_ms(t_simulation *simulation, long long duration_ms)
{
	long long	end_time;

	end_time = get_current_time_ms() + duration_ms;
	while (get_current_time_ms() < end_time)
	{
		if (is_simulation_stopped(simulation) == 1)
			return ;
		usleep(500);
	}
}
