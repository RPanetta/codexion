/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 18:12:18 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/17 18:30:31 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_coder *coder, const char *message)
{
	t_simulation	*simulation;
	long long		elapsed_time;

	simulation = coder->simulation;
	pthread_mutex_lock(&simulation->log_mutex);
	pthread_mutex_lock(&simulation->stop_mutex);
	if (simulation->should_stop == 0)
	{
		elapsed_time = get_elapsed_time_ms(simulation->start_time);
		printf("%lld %d %s\n", elapsed_time, coder->id, message);
	}
	pthread_mutex_unlock(&simulation->stop_mutex);
	pthread_mutex_unlock(&simulation->log_mutex);
}
