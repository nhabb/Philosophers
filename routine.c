/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:22:08 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/12 12:59:44 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_think(t_philo *philo)
{
    wrt_stat(THINKING,philo,DEBU_STAT);
}


void philo_eat(t_philo *philo)
{
    handle_mutex(&philo->primray->fork,LOCK);
    wrt_stat(TAKE_FIRST,philo,DEBU_STAT);
    handle_mutex(&philo->secondary->fork,LOCK);
    wrt_stat(TAKE_SECOND,philo,DEBU_STAT);
    set_long(&philo->philo_mutex,&philo->last_meal_t,get_timestamp());
    philo->meal_counter++;
    wrt_stat(EATING,philo,DEBU_STAT);
    ft_usleep(philo->data->tte,philo->data);
    if (philo->data->num_meals > 0 && philo->meal_counter == philo->data->num_meals)
        set_boolean(&philo->philo_mutex, &philo->full,true);
    handle_mutex(&philo->primray->fork,UNLOCK);
    handle_mutex(&philo->secondary->fork,UNLOCK);
}

//wait for all philos,synchronize the threads
void *routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *) data;
    thread_wait(philo->data);
    while (!sim_finished(data))
    {
        if (philo->full)
            break;
        philo_eat(philo);
        wrt_stat(SLEEPING,philo,DEBU_STAT);
        ft_usleep(philo->data->tts,philo->data);
        philo_think(philo);
    }
    return NULL;
}


void start_simulation(t_data *data)
{
    int i;

    i = -1;
    if (data->num_meals == 0)
        return ;
    else if (data->num_philo == 1)
        ;
    else
    {
        while (++i < data->num_philo)
            handle_thread(&data->philos[i].thread_id, routine, &data->philos[i], CREATE);

    }
    data->sim_start = get_timestamp();
    set_boolean(&data->data_mutex,&data->threads_sync,true);
    i = -1;
    while (++i < data->num_philo)
        handle_thread(&data->philos[i].thread_id,NULL,NULL,JOIN);
    
}
