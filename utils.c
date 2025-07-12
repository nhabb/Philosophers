/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:14:20 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/12 12:59:49 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long get_timestamp(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void    ft_usleep(long usec,t_data *data)
{
    long    start;
    long elapsed;
    long rem;
    start = (get_timestamp() / 1000);
    while ((get_timestamp() / 1000) - start < usec)
    {
        if (sim_finished(data))
            break;
        elapsed = (get_timestamp() / 1000) - start;
        rem = usec - elapsed;
        if (rem > 1000)
            usleep(usec / 2);
        else
        {
            while ((get_timestamp() / 1000) - start < usec)
                ;
        }
    }
}