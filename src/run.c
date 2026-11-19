/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 13:08:05 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 16:01:34 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Stores the simulation's start time, which serves as “time zero” for the logs.
//Sets each coder's last_compile_start to start_time,
//so the burnout deadline before the first compilation
//is measured from the simulation's start
static void	set_start_times(t_simulation *simulation)
{
	int		index;
	t_coder	*coder;

	simulation->start_time = get_current_time_ms();
	index = 0;
	while (index < simulation->config.number_of_coders)
	{
		coder = &simulation->coders[index];
		coder->last_compile_start = simulation->start_time;
		index++;
	}
}

//returns the number of threads successfully created.
//If all threads are created, it returns number_of_coders.
//If creating the thread at index 3 fails, it returns 3,
//because threads 0, 1, and 2 were created successfully.
static int	create_coder_threads(t_simulation *simulation)
{
	int		index;
	int		result;
	t_coder	*coder;

	index = 0;
	while (index < simulation->config.number_of_coders)
	{
		coder = &simulation->coders[index];
		result = pthread_create(&coder->thread, NULL, coder_routine, coder);
		if (result != 0)
			return (index);
		index++;
	}
	return (index);
}

//pthread_join means “wait for this thread to finish.”
//Without it, main could destroy resources while
//the threads are still using them.
//It takes count so it only waits for threads that were successfully created.
static void	join_coder_threads(t_simulation *simulation, int count)
{
	int	index;

	index = 0;
	while (index < count)
	{
		pthread_join(simulation->coders[index].thread, NULL);
		index++;
	}
}

//Set the timestamps - create the threads - wait for them to finish.
//If not all threads could be created, it first signals the simulation
//to stop so the existing threads can exit, then waits for them to finish
//and returns an error
int	run_simulation(t_simulation *simulation)
{
	int	created_count;

	set_start_times(simulation);
	created_count = create_coder_threads(simulation);
	if (created_count < simulation->config.number_of_coders)
	{
		stop_simulation(simulation);
		join_coder_threads(simulation, created_count);
		return (print_error("Thread creation failed"));
	}
	join_coder_threads(simulation, created_count);
	return (0);
}
