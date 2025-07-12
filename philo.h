#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo	t_philo;
typedef pthread_mutex_t	t_mutex;

typedef struct s_data {
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_meals;
	long			start_time;
	bool			sim_end;
	t_mutex			sim_mutex;
	t_mutex			*forks;
	t_mutex			print_mutex;
	t_philo			*philos;
}	t_data;

struct s_philo {
	int				id;
	pthread_t		thread;
	int				meals_eaten;
	long			last_meal;
	t_mutex			meal_mutex;
	t_mutex			*left_fork;
	t_mutex			*right_fork;
	t_data			*data;
};

// Parsing
bool	parse_args(t_data *data, int argc, char **argv);

// Initialization
bool	init_data(t_data *data);
bool	init_philos(t_data *data);

// Time
long	get_time_ms(void);
void	precise_sleep(int ms);

// Threads
void	start_simulation(t_data *data);
void	*philo_routine(void *arg);

// Monitoring
void	*monitor_routine(void *arg);

// Printing
void	print_status(t_philo *philo, char *status);

// Mutex utils
void	mutex_init(t_mutex *mutex);
void	mutex_destroy(t_mutex *mutex);
void	mutex_lock(t_mutex *mutex);
void	mutex_unlock(t_mutex *mutex);

// Cleanup
void	cleanup_data(t_data *data);

// Add these declarations
bool simulation_ended(t_data *data);
void safe_unlock(t_mutex *mutex1, t_mutex *mutex2);

#endif