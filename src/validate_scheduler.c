/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scheduler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 17:04:21 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/12 17:06:16 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	validate_scheduler(const char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0 || strcmp(scheduler, "edf") == 0)
		return (0);
	return (1);
}
