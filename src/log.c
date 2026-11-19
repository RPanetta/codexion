/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:12:18 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 12:02:59 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Only prints if the simulation has not stopped
void	print_status(t_simulation *simulation, int coder_id, char *message)
{
	long long		elapsed_time;

	pthread_mutex_lock(&simulation->log_mutex);
	if (is_simulation_stopped(simulation) == 0)
	{
		elapsed_time = get_elapsed_time_ms(simulation->start_time);
		printf("%lld %d %s\n", elapsed_time, coder_id, message);
	}
	pthread_mutex_unlock(&simulation->log_mutex);
}

//The burnout message must be printed even if the simulation
//is already marked as stopped
void	print_burnout(t_simulation *simulation, int coder_id)
{
	long long	elapsed_time;

	pthread_mutex_lock(&simulation->log_mutex);
	elapsed_time = get_elapsed_time_ms(simulation->start_time);
	printf("%lld %d burned out\n", elapsed_time, coder_id);
	pthread_mutex_unlock(&simulation->log_mutex);
}
