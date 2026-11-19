/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 11:20:49 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 11:33:06 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Locks the mutex, copies the value of should_stop
//into a variable, and unlocks the mutex.
//Pattern: lock, read or write, unlock and return.
int	is_simulation_stopped(t_simulation *simulation)
{
	int	stopped;

	pthread_mutex_lock(&simulation->stop_mutex);
	stopped = simulation->should_stop;
	pthread_mutex_unlock(&simulation->stop_mutex);
	return (stopped);
}

//Returns 1 only if this call stopped the simulation,
//and 0 if it was already stopped.
//This will later be used for the burned out:
//if stop_simulation returns 1, print the burnout message
int	stop_simulation(t_simulation *simulation)
{
	int	is_first_stop;

	is_first_stop = 0;
	pthread_mutex_lock(&simulation->stop_mutex);
	if (simulation->should_stop == 0)
	{
		simulation->should_stop = 1;
		is_first_stop = 1;
	}
	pthread_mutex_unlock(&simulation->stop_mutex);
	return (is_first_stop);
}
