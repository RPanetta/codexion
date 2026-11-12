/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:35:14 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/12 16:54:01 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Converts a single number
int	parse_number(const char *text, int *number)
{
	int	index;
	int	value;
	int	digit;

	if (text[0] == '\0')
		return (1);
	index = 0;
	value = 0;
	while (text[index] != '\0')
	{
		if (text[index] < '0' || text[index] > '9')
			return(1);
		digit = text[index] - '0';
		if (value > (INT_MAX - digit) / 10)
			return (1);
		value = value * 10 + digit;
		index++;
	}
	*number = value;
	return (0);
}

//Fills the configuration
int	parse_confi(char *argv[], t_config *config)
{
	if (parse_number(argv[1], &config->number_of_coders)
		|| parse_number(argv[2], &config->time_to_burnout)
		|| parse_number(argv[3], &config->time_to_compile)
		|| parse_number(argv[4], &config->time_to_debug)
		|| parse_number(argv[5], &config->time_to_refactor)
		|| parse_number(argv[6], &config->number_of_compiles_required)
		|| parse_number(argv[7], &config->dongle_cooldown))
		return (1);
	config->scheduler = argv[8];
	return (0);
}
