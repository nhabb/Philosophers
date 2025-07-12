/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:18:03 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/12 12:59:32 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
#include <limits.h>
# include <stdbool.h>
# include <unistd.h>
#include <errno.h>
# include <stdlib.h>
# include <stdio.h>
#define DEBU_STAT 0
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
	bool	threads_sync;
	t_fork	*forks;
	t_philo	*philos;
	mtx		data_mutex;
	mtx		wrt_mutex;
}t_data;



typedef struct s_philo {
	int			id;
	long		meal_counter;
	bool		full;
	t_fork		*primray;
	t_fork		*secondary;
	pthread_t	thread_id;
	long	last_meal_t;
	t_data		*data;
	mtx			philo_mutex;
} t_philo;

typedef enum s_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
} t_opcode;

typedef enum e_stat
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST,
	TAKE_SECOND,
	DIED	
}	t_philo_stat;


long get_timestamp(void);
bool parse_input(t_data *data, char **argv);
long   ft_atol(const char *str);
bool	ft_isdigit(int c);
const char *is_valid(const char *str);
void *handle_malloc(size_t size);
void handle_mutex(mtx *mutex, t_opcode opcode);
static void handle_error(int status, t_opcode opcode);
static bool handle_error_helper(int status,t_opcode opcode);
static void thread_error(int status, t_opcode opcode);
static bool thread_error_helper(int status, t_opcode opcode);
void handle_thread(pthread_t *thread,void *(*foo)(void *)
                ,void *data, t_opcode opcode);
void init_data(t_data *data);
static void init_philo(t_data *data);
static void take_forks(t_philo *philo,t_fork *forks,int pos);
void set_boolean(mtx *mutex,bool *dest,bool val);
bool get_boolean(mtx *mutex,bool *val);
void set_long(mtx *mutex,long *dest,long val);
long get_long(mtx *mutex,long *val);
bool    sim_finished(t_data *data);
void thread_wait(t_data *data);
long get_timestamp(void);
void    ft_usleep(long usec,t_data *data);
void    wrt_stat(t_philo_stat stat,t_philo *philo,bool debug);
void philo_eat(t_philo *philo);
void philo_think(t_philo *philo);
void start_simulation(t_data *data);
#endif
