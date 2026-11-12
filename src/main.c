/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:12:36 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/12 17:30:14 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char *argv[])
{
	t_config	config;

	if (argc != 9)
		return (print_error("Expected exactly 8 arguments"));
	if (parse_config(argv, &config))
		return (print_error("Invalid numeric argument"));
	if (config.number_of_coders == 0)
		return (print_error("The number of coders must be greater than 0"));
	if (validate_scheduler(config.scheduler))
		return (print_error("Scheduler must be fifo or edf"));
	return (0);
}
