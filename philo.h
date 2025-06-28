/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:18:03 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/28 22:03:17 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
#include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef pthread_mutex_t mtx;
typedef struct s_philo t_philo;

typedef struct s_fork {
	mtx fork;
	int	fork_id;
} t_fork;

typedef struct s_data
{
	long 	num_philo;
	long	ttd;
	long	tte;
	long	tts;
	long	num_meals;
	long	sim_start;
	bool	sim_end;
	t_fork	*forks;
	t_philo	*philos;
}t_data;



typedef struct s_philo {
	int			id;
	long		meal_counter;
	bool		full;
	t_fork		*left;
	t_fork		*right;
	pthread_t	thread_id;
	long long	last_meal_t;
	t_data		*data;
} t_philo;

long long get_time_ms(void);
bool parse_input(t_data *data,char **argv);
long   ft_atol(const char *str);
bool	ft_isdigit(int c);
static const char *is_valid(const char *str);
void init_data(t_data *args, int argc, char **argv);
void init_forks(t_data *args, int i);
void init_philos(t_philo *philos, t_data *args, int i);
void join_philos(t_philo *philos, int count, int i);
void destroy_forks(t_data *args, int i);
void *philosopher_routine(void *arg);
int	get_stop(t_data *args);
void set_stop(t_data *args);

#endif
