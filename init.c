/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 09:30:57 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/12 12:59:12 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void take_forks(t_philo *philo,t_fork *forks,int pos)
{
    int philo_num;

    philo_num = philo->data->num_philo;
    philo->primray = &forks[(pos + 1) % philo_num];
    philo->secondary = &forks[pos];
    if (philo->id %2 == 0)
    {
        philo->primray = &forks[pos];
        philo->secondary = &forks[(pos + 1) % philo_num];
    }
}


static void init_philo(t_data *data)
{
    int i;
    t_philo *philo;

    i = -1;
    while (++i < data->num_philo)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = false;
        philo->meal_counter = 0;
        philo->data = data;
        handle_mutex(&philo->philo_mutex,INIT);
        take_forks(philo,data->forks,i);
    }
}


void init_data(t_data *data)
{
    int i;
    
    i = -1;
    data->sim_end = false;
    data->threads_sync = false;
    data->philos = handle_malloc(sizeof(t_philo) * data->num_philo);
    data->forks = handle_malloc(sizeof(t_fork) * data->num_philo);
    handle_mutex(&data->data_mutex,INIT);
    handle_mutex(&data->wrt_mutex,INIT);
    while(++i < data->num_philo)
    {
        handle_mutex(&data->forks[i].fork,INIT);
        data->forks[i].fork_id = i;
    }
    init_philo(data);
}