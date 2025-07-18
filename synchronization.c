/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 10:09:17 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/18 16:19:46 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	monitor_helper(t_data *data, long current_time, bool *all_full)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		last_meal = data->philos[i].last_meal;
		if (check_death(data, current_time, last_meal, i) == 0)
			return (pthread_mutex_unlock(&data->philos[i].meal_mutex), 0);
		if (data->num_meals > 0 && data->philos[i].meals_eaten < data->num_meals)
			*all_full = false;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	long	current_time;
	bool	all_full;

	data = (t_data *)arg;
	while (!simulation_ended(data))
	{
		all_full = true;
		current_time = get_time_ms();
		if (!monitor_helper(data, current_time, &all_full))
			return (NULL);
		if (check_full(data, all_full) == 0)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void precise_sleep(int ms)
{
    long start = get_time_ms();
    long end = start + ms;
    long current;
    long remaining;
    
    while ((current = get_time_ms()) < end)
    {
        remaining = end - current;
        if (remaining > 1) {
            // Sleep for 80% of remaining time to avoid oversleeping
            usleep(remaining * 800);
        } else {
            // Busy-wait for the last millisecond for precision
            while (get_time_ms() < end)
                ;
        }
    }
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	mutex_lock(&philo->data->sim_mutex);
	if (philo->data->sim_end)
	{
		mutex_unlock(&philo->data->sim_mutex);
		return ;
	}
	mutex_unlock(&philo->data->sim_mutex);
	time = get_time_ms() - philo->data->start_time;
	mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", time, philo->id, status);
	mutex_unlock(&philo->data->print_mutex);
}

void	cleanup_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
	{
		mutex_destroy(&data->philos[i].meal_mutex);
		mutex_destroy(&data->forks[i]);
	}
	mutex_destroy(&data->sim_mutex);
	mutex_destroy(&data->print_mutex);
	free(data->philos);
	free(data->forks);
}

bool simulation_ended(t_data *data)
{
    bool ended;
    
    pthread_mutex_lock(&data->sim_mutex);
    ended = data->sim_end;
    pthread_mutex_unlock(&data->sim_mutex);
    return ended;
}

void safe_unlock(t_mutex *mutex1, t_mutex *mutex2)
{
    if (mutex1 && mutex1 != mutex2) 
        pthread_mutex_unlock(mutex1);
    if (mutex2 && mutex1 != mutex2) 
        pthread_mutex_unlock(mutex2);
}