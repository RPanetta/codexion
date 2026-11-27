/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:17:20 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/26 16:09:00 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <time.h>
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
	int				has_dongles;
}	t_coder;

typedef struct s_heap_node
{
	long long	key;
	int			coder_id;
}	t_heap_node;

typedef struct s_heap
{
	t_heap_node	*nodes;
	int			size;
	int			capacity;
}	t_heap;

struct s_simulation
{
	t_config		config;
	long long		start_time;
	int				should_stop;
	t_coder			*coders;
	t_dongle		*dongles;
	pthread_mutex_t	log_mutex;
	pthread_mutex_t	stop_mutex;
	long long		next_ticket;
	t_heap			waiting_queue;
	t_heap_node		*skipped_nodes;
	pthread_mutex_t	dongle_mutex;
	pthread_cond_t	dongle_condition;
} ;

int			print_error(char *message);
int			parse_number(const char *text, int *number);
int			parse_config(char *argv[], t_config *config);
int			validate_scheduler(const char *scheduler);
long long	get_current_time_ms(void);
long long	get_elapsed_time_ms(long long start_time);
void		sleep_ms(t_simulation *simulation, long long duration_ms);
int			init_simulation(t_simulation *simulation);
void		destroy_coder_mutexes(t_simulation *simulation, int count);
void		destroy_global_mutexes(t_simulation *simulation);
void		free_memory(t_simulation *simulation);
void		destroy_simulation(t_simulation *simulation);
int			is_simulation_stopped(t_simulation *simulation);
int			stop_simulation(t_simulation *simulation);
void		print_status(t_simulation *simulation, int coder_id, char *message);
void		print_burnout(t_simulation *simulation, int coder_id);
void		*coder_routine(void *argument);
int			run_simulation(t_simulation *simulation);
int			heap_init(t_heap *heap, int capacity);
void		heap_destroy(t_heap *heap);
int			heap_push(t_heap *heap, t_heap_node node);
int			is_smaller_at(t_heap *heap, int first_index, int second_index);
void		swap_at(t_heap *heap, int first_index, int second_index);
void		heap_move_up(t_heap *heap, int index);
void		heap_move_down(t_heap *heap, int index);
t_heap_node	heap_pop(t_heap *heap);
int			get_right_dongle_index(t_simulation *simulation, int coder_id);
int			are_dongles_ready(t_simulation *simulation, int coder_id);
long long	get_next_cooldown_end(t_simulation *simulation);
int			pop_ready_coder(t_simulation *simulation, t_heap_node *ready_node);
int			assign_ready_dongles(t_simulation *simulation);
int			acquire_dongles(t_coder *coder);
void		release_dongles(t_coder *coder);

#endif