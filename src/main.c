/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:12:36 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/17 16:56:19 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char *argv[])
{
	t_config	config;
	t_simulation	simulation;

	if (argc != 9)
		return (print_error("Expected exactly 8 arguments"));
	if (parse_config(argv, &config))
		return (print_error("Invalid numeric argument"));
	if (config.number_of_coders == 0)
		return (print_error("The number of coders must be greater than 0"));
	if (validate_scheduler(config.scheduler))
		return (print_error("Scheduler must be fifo or edf"));
	simulation.config = config;
	if (init_simulation(&simulation) != 0)
		return (1);
	printf("coder 1 id: %d\n", simulation.coders[0].id);
	printf("coder 1 count: %d\n", simulation.coders[0].compile_count);
	printf("dongle 1 taken: %d\n", simulation.dongles[0].is_taken);
	destroy_simulation(&simulation);
	return (0);
}
