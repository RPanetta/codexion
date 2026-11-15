/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 17:15:56 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/14 17:15:56 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long   get_current_time_ms(void)
{
    struct timeval  time_value;
    long long       seconds_in_ms;
    long long       microseconds_in_ms;

    gettimeofday(&time_value, NULL);
    seconds_in_ms = time_value.tv_sec * 1000;
    microseconds_in_ms = time_value.tv_usec / 1000;
    return (seconds_in_ms + microseconds_in_ms);
}

long long   get_elapsed_time_ms(long long start_time)
{
    long long   current_time;

    current_time = get_current_time_ms();
    return (current_time - start_time);
}

void    sleep_ms(long long duration_ms)
{
    long long   end_time;

    end_time = get_current_time_ms() + duration_ms;
    while(get_current_time_ms() < end_time)
        usleep(500);
}