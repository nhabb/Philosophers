#include "philo.h"

// long	get_time_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
// }



// void precise_sleep(int ms)
// {
//     long start = get_time_ms();
//     long now;
    
//     while (1)
//     {
//         now = get_time_ms();
//         if (now - start >= ms)
//             break;
//         usleep(500);
//     }
// }


// void	print_status(t_philo *philo, char *status)
// {
// 	long	time;

// 	mutex_lock(&philo->data->sim_mutex);
// 	if (philo->data->sim_end)
// 	{
// 		mutex_unlock(&philo->data->sim_mutex);
// 		return ;
// 	}
// 	mutex_unlock(&philo->data->sim_mutex);
// 	time = get_time_ms() - philo->data->start_time;
// 	mutex_lock(&philo->data->print_mutex);
// 	printf("%ld %d %s\n", time, philo->id, status);
// 	mutex_unlock(&philo->data->print_mutex);
// }

// #include "philo.h"

// void	cleanup_data(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < data->num_philos)
// 	{
// 		mutex_destroy(&data->philos[i].meal_mutex);
// 		mutex_destroy(&data->forks[i]);
// 	}
// 	mutex_destroy(&data->sim_mutex);
// 	mutex_destroy(&data->print_mutex);
// 	free(data->philos);
// 	free(data->forks);
// }


// #include "philo.h"

// void	mutex_init(t_mutex *mutex)
// {
// 	if (pthread_mutex_init(mutex, NULL) != 0)
// 	{
// 		printf("Error: mutex init failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	mutex_destroy(t_mutex *mutex)
// {
// 	if (pthread_mutex_destroy(mutex) != 0)
// 	{
// 		printf("Error: mutex destroy failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	mutex_lock(t_mutex *mutex)
// {
// 	if (pthread_mutex_lock(mutex) != 0)
// 	{
// 		printf("Error: mutex lock failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	mutex_unlock(t_mutex *mutex)
// {
// 	if (pthread_mutex_unlock(mutex) != 0)
// 	{
// 		printf("Error: mutex unlock failed\n");
// 		exit(EXIT_FAILURE);
// 	}
// }