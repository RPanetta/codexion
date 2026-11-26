/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/17 15:11:54 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/26 16:12:18 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Reserve the lists of coders and dongles
//total = the number of coders (same to dongles: is one per coder)
static int	allocate_memory(t_simulation *simulation)
{
	int	total;

	total = simulation->config.number_of_coders;
    simulation->waiting_queue.nodes = NULL;
	simulation->coders = malloc(sizeof(t_coder) * total);
    simulation->dongles = malloc(sizeof(t_dongle) * total);
    simulation->skipped_nodes = malloc(sizeof(t_heap_node) * total);
	if (simulation->coders == NULL || simulation->dongles == NULL
        || simulation->skipped_nodes == NULL)
    {
        free_memory(simulation);
        return (1);
    }
	if (heap_init(&simulation->waiting_queue, total) != 0)
	{
		free_memory(simulation);
		return (1);
	}
	return (0);
}

//Iterate through all the dongles, setting each one to be free
//(is_taken = 0) and available from the start (available_at = 0)
static void	init_dongles(t_simulation *simulation)
{
	int	index;

	index = 0;
	while (index < simulation->config.number_of_coders)
	{
		simulation->dongles[index].is_taken = 0;
		simulation->dongles[index].available_at = 0;
		index++;
	}
}

//Create log_mutex and stop_mutex
//each failure undoes exactly what was created before
static int	init_global_mutexes(t_simulation *simulation)
{
	if (pthread_mutex_init(&simulation->log_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&simulation->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&simulation->log_mutex);
		return (1);
	}
    if (pthread_mutex_init(&simulation->dongle_mutex, NULL) != 0)
    {
        pthread_mutex_destroy(&simulation->stop_mutex);
        pthread_mutex_destroy(&simulation->log_mutex);
		return (1);
    }
    if (pthread_cond_init(&simulation->dongle_condition, NULL) != 0)
    {
        pthread_mutex_destroy(&simulation->dongle_mutex);
        pthread_mutex_destroy(&simulation->stop_mutex);
        pthread_mutex_destroy(&simulation->log_mutex);
        return (1);
    }
	return (0);
}

//Assign initial values ​​to each coder and create its mutex
static int	init_coders(t_simulation *simulation)
{
	int		index;
	t_coder	*coder;

	index = 0;
	while (index < simulation->config.number_of_coders)
	{
		coder = &simulation->coders[index]; //stores the address of the current coder in a pointer
		coder->id = index + 1; //each coder receives their id
		coder->compile_count = 0;
		coder->last_compile_start = 0;
		coder->simulation = simulation;
        coder->has_dongles = 0;
		if (pthread_mutex_init(&coder->data_mutex, NULL) != 0)
		{
			destroy_coder_mutexes(simulation, index);
			return (1);
		}
		index++;
	}
	return (0);
}

//Call all of the above, in order
//operations in order: memory → dongles → global mutexes → coders.
//Each failed (if condition) undoes exactly what was done previously
int	init_simulation(t_simulation *simulation)
{
    simulation->next_ticket = 0;
	simulation->should_stop = 0;
	if (allocate_memory(simulation) != 0)
		return (print_error("Memory allocation failed"));
	init_dongles(simulation);
	if (init_global_mutexes(simulation) != 0)
	{
		free_memory(simulation);
		return (print_error("Mutex initialization failed"));
	}
	if (init_coders(simulation) != 0)
	{
		destroy_global_mutexes(simulation);
		free_memory(simulation);
		return (print_error("Mutex initialization failed"));
	}
	return (0);
}
