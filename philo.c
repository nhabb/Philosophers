/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:23:39 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/28 22:06:40 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int main(int argc, char **argv)
{
	t_data *data;
	// t_philo *philos;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s num_philos time_to_die time_to_eat time_to_sleep [meals]\n", argv[0]);
		return (-1);
	}
	if (parse_input(data,argv) == false)
		return 1;
	printf("%ld %ld %ld %ld %ld",data->num_philo,data->ttd,data->tts,data->tte,data->num_meals);
	init_data(&data);
	start_routine(&data);
	//philos full || philo died
	free_data(&data);
	// init_forks(&data, 0);
	// philos = malloc(sizeof(t_philo) * data.num_philo);
	// if (!philos)
	// 	return (1);
	// init_philos(philos, &data, 0);
	// join_philos(philos, data.num_philo, 0);
	// destroy_forks(&data, 0);
	// free(data.forks);
	// free(philos);
	return (0);
}
