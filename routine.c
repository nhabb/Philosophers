// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   routine.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/27 19:22:08 by nhaber            #+#    #+#             */
// /*   Updated: 2025/06/28 14:56:15 by nhaber           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// long long get_time_ms(void)
// {
// 	struct timeval time;
// 	gettimeofday(&time, NULL);
// 	return (time.tv_sec * 1000LL) + (time.tv_usec / 1000);
// }

// void init_data(t_data *args, int argc, char **argv)
// {
// 	args->philo_count = atoi(argv[1]);
// 	args->t_die = atoi(argv[2]);
// 	args->t_eat = atoi(argv[3]);
// 	args->t_sleep = atoi(argv[4]);
//     if (argc == 6)
//         args->meals_required = atoi(argv[5]);
//     // else
//     args->meals_required = -1;
// 	args->forks = malloc(sizeof(pthread_mutex_t) * args->philo_count);
// 	if (!args->forks)
// 		exit(1);
// }

// void init_forks(t_data *args, int i)
// {
// 	if (i < args->philo_count)
// 	{
// 		pthread_mutex_init(&args->forks[i], NULL);
// 		init_forks(args, i + 1);
// 	}
// }

// void init_philos(t_philo *philos, t_data *args, int i)
// {
// 	if (i < args->philo_count)
// 	{
//         set_stop(args);
// 		philos[i].id = i + 1;
// 		philos[i].args = args;
// 		philos[i].last_meal = get_time_ms();
// 		philos[i].meals_eaten = 0;
// 		pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]);
// 		init_philos(philos, args, i + 1);
// 	}
// }

// void join_philos(t_philo *philos, int count, int i)
// {
// 	if (i < count)
// 	{
// 		pthread_join(philos[i].thread, NULL);
// 		join_philos(philos, count, i + 1);
// 	}
// }

// void destroy_forks(t_data *args, int i)
// {
// 	if (i < args->philo_count)
// 	{
// 		pthread_mutex_destroy(&args->forks[i]);
// 		destroy_forks(args, i + 1);
// 	}
// }

// int get_stop(t_data *args)
// {
//     int val;
//     pthread_mutex_lock(&args->stop_mutex);
//     val = args->stop;
//     pthread_mutex_unlock(&args->stop_mutex);
//     return val;
// }

// void set_stop(t_data *args)
// {
//     pthread_mutex_lock(&args->stop_mutex);
//     args->stop = 1;
//     pthread_mutex_unlock(&args->stop_mutex);
// }






