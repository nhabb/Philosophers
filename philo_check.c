/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:25:29 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/18 15:25:37 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_death(t_data *data,int current_time,int last_meal,int i)
{
    if (current_time - last_meal > data->time_to_die)
    {
        long recheck_time = get_time_ms();
        if (recheck_time - last_meal >= data->time_to_die)
        {
            pthread_mutex_lock(&data->print_mutex);
            if (!simulation_ended(data)) {
                printf("%ld %d died\n", recheck_time - data->start_time, data->philos[i].id);
                pthread_mutex_lock(&data->sim_mutex);
                data->sim_end = true;
                pthread_mutex_unlock(&data->sim_mutex);
            }
            pthread_mutex_unlock(&data->print_mutex);
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            return (0);
        }
    }
    return (1);
}

int check_full(t_data *data,bool all_full)
{
    if (data->num_meals > 0 && all_full)
    {
        pthread_mutex_lock(&data->sim_mutex);
        data->sim_end = true;
        pthread_mutex_unlock(&data->sim_mutex);
        return 0;
    }
    return 1;
}