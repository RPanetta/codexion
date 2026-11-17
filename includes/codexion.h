/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:17:20 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/17 18:26:02 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdio.h>

typedef struct s_config
{
	int			number_of_coders;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_debug;
	int			time_to_refactor;
	int			number_of_compiles_required;
	int			dongle_cooldown;
	const char	*scheduler;
}	t_config;

typedef struct s_simulation	t_simulation;

typedef struct s_dongle
{
	int			is_taken;
	long long	available_at;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compile_count;
	long long		last_compile_start;
	pthread_t		thread;
	pthread_mutex_t	data_mutex;
	t_simulation	*simulation;
}	t_coder;

struct s_simulation
{
	t_config		config;
	long long		start_time;
	int				should_stop;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
};

int			print_error(char *message);
int			parse_number(const char *text, int *number);
int			parse_config(char *argv[], t_config *config);
int			validate_scheduler(const char *scheduler);
long long	get_current_time_ms(void);
long long	get_elapsed_time_ms(long long start_time);
void		sleep_ms(long long duration_ms);
int			init_simulation(t_simulation *simulation);
void		destroy_coder_mutexes(t_simulation *simulation, int count);
void		destroy_global_mutexes(t_simulation *simulation);
void		free_memory(t_simulation *simulation);
void		destroy_simulation(t_simulation *simulation);

#endif