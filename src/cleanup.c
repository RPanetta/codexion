/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:47:51 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/17 18:30:04 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//destroy the coders mutexes
//destroy_coder_mutexes takes the number of mutexes to destroy (count)
void	destroy_coder_mutexes(t_simulation *simulation, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		pthread_mutex_destroy(&simulation->coders[index].data_mutex);
		index++;
	}
}

//destroy stop_mutex and log_mutex
void	destroy_global_mutexes(t_simulation *simulation)
{
	pthread_mutex_destroy(&simulation->stop_mutex);
	pthread_mutex_destroy(&simulation->log_mutex);
}

//free the lists
void	free_memory(t_simulation *simulation)
{
	free(simulation->coders);
	free(simulation->dongles);
}

//clean everything at the end of the program
void	destroy_simulation(t_simulation *simulation)
{
	destroy_coder_mutexes(simulation, simulation->config.number_of_coders);
	destroy_global_mutexes(simulation);
	free_memory(simulation);
}
