/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:18:20 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/22 15:18:20 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int get_right_dongle_index(t_simulation *simulation, int coder_id)
{
    return ((coder_id + 1) % simulation->config.number_of_coders);
}

//dongle is ready if it's not taken and its cooldown has ended.
//If it's taken or still on cooldown, it's not ready
static int  is_dongle_ready(t_simulation *simulation, int dongle_index)
{
    t_dongle    *dongle;

    dongle = &simulation->dongles[dongle_index];
    if (dongle->is_taken == 1)
        return (0);
    if (get_current_time_ms() < dongle->available_at)
        return (0);
    return (1);
}

//Does this coder have both dongles ready?
//if the left and right dongles are the same dongle (which happens when
//there's only one coder), return 0 because there aren't two distinct dongles
int are_dongles_ready(t_simulation *simulation, int coder_id)
{
    int left_index;
    int right_index;

    left_index = coder_id;
    right_index = get_right_dongle_index(simulation, coder_id);
    if (left_index == right_index)
        return (0);
    if (is_dongle_ready(simulation, left_index) == 0)
        return (0);
    if (is_dongle_ready(simulation, right_index) == 0)
        return (0);
    return (1);
}

long long   get_next_cooldown_end(t_simulation *simulation)
{
	long long	now;
	long long	earliest;
	t_dongle	*dongle;
	int			index;

	now = get_current_time_ms();
	earliest = 0;
	index = 0;
	while (index < simulation->config.number_of_coders)
	{
		dongle = &simulation->dongles[index];
		if (dongle->is_taken == 0 && dongle->available_at > now)
		{
			if (earliest == 0 || dongle->available_at < earliest)
				earliest = dongle->available_at;
		}
		index++;
	}
	return (earliest);
}
