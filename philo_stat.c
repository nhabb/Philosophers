/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 21:18:36 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/02 22:34:12 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void debug_stat(t_philo_stat stat,t_philo *philo, long elapsed)
// {
//     if ((stat == TAKE_FIRST || stat == TAKE_SECOND) && !sim_finished(philo->data))
//         printf("%ld %d has taken a fork\n",elapsed,philo->id);
//     else if (stat == EATING && !sim_finished(philo->data))
//         printf("%ld %d is eating\n",elapsed,philo->id);
//     else if (stat == SLEEPING && !sim_finished(philo->data))
//         printf("%ld %d is sleeping\n",elapsed,philo->id);
//     else if (stat == THINKING && !sim_finished(philo->data))
//         printf("%ld %d is thinking\n",elapsed,philo->id);
//     else if (stat == DIED)
//         printf("%ld %d died\n",elapsed,philo->id);
// }

void    wrt_stat(t_philo_stat stat,t_philo *philo,bool debug)
{
    long    elapsed;

    elapsed = get_timestamp() - philo->data->sim_start;
    if (philo->full)
        return ;
    handle_mutex(&philo->data->wrt_mutex,LOCK);
    // if (debug)
    //     debug_stat(stat,philo,elapsed);
    // else
    // {
        if ((stat == TAKE_FIRST || stat == TAKE_SECOND) && !sim_finished(philo->data))
            printf("%ld %d has taken a fork\n",elapsed,philo->id);
        else if (stat == EATING && !sim_finished(philo->data))
            printf("%ld %d is eating\n",elapsed,philo->id);
        else if (stat == SLEEPING && !sim_finished(philo->data))
            printf("%ld %d is sleeping\n",elapsed,philo->id);
        else if (stat == THINKING && !sim_finished(philo->data))
            printf("%ld %d is thinking\n",elapsed,philo->id);
        else if (stat == DIED)
            printf("%ld %d died\n",elapsed,philo->id);
    // }
    handle_mutex(&philo->data->wrt_mutex,UNLOCK);
}