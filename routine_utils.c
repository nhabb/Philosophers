/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 16:19:05 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/18 16:19:06 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_mutex *mutex)
{
	pthread_mutex_init(mutex, NULL);
}

void	mutex_destroy(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

void	mutex_lock(t_mutex *mutex)
{
	pthread_mutex_lock(mutex);
}

void	mutex_unlock(t_mutex *mutex)
{
	pthread_mutex_unlock(mutex);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}