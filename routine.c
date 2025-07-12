#include "philo.h"


void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    t_mutex *first_fork;
    t_mutex *second_fork;
    
    if (philo->id % 2 == 0) {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    } else {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }

    while (!simulation_ended(philo->data))
    {
        // Take first fork
        pthread_mutex_lock(first_fork);
        print_status(philo, "has taken a fork");
        
        // Check if simulation ended while waiting for fork
        if (simulation_ended(philo->data)) {
            pthread_mutex_unlock(first_fork);
            break;
        }
        
        // Handle single philosopher case
        if (philo->data->num_philos == 1) {
            precise_sleep(philo->data->time_to_die);
            pthread_mutex_unlock(first_fork);
            break;
        }
        
        // Take second fork
        pthread_mutex_lock(second_fork);
        print_status(philo, "has taken a fork");
        
        // Check if simulation ended while waiting for fork
        if (simulation_ended(philo->data)) {
            safe_unlock(first_fork, second_fork);
            break;
        }
        
        // Start eating
        print_status(philo, "is eating");
        
        // Update meal tracking
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal = get_time_ms();
        philo->meals_eaten++;
        pthread_mutex_unlock(&philo->meal_mutex);
        
        // Eat for specified time
        precise_sleep(philo->data->time_to_eat);
        
        // Release forks
        pthread_mutex_unlock(first_fork);
        pthread_mutex_unlock(second_fork);
        
        // Sleep and think
        print_status(philo, "is sleeping");
        precise_sleep(philo->data->time_to_sleep);
        print_status(philo, "is thinking");
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_data *data = (t_data *)arg;
    int i;
    long current_time;
    long last_meal;
    bool all_full;
    
    while (!simulation_ended(data))
    {
        i = 0;
        all_full = true;
        while (i < data->num_philos)
        {
            pthread_mutex_lock(&data->philos[i].meal_mutex);
            last_meal = data->philos[i].last_meal;
            current_time = get_time_ms();
            
            // Check for death
            if (current_time - last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->print_mutex);
                printf("%ld %d died\n", current_time - data->start_time, data->philos[i].id);
                pthread_mutex_lock(&data->sim_mutex);
                data->sim_end = true;
                pthread_mutex_unlock(&data->sim_mutex);
                pthread_mutex_unlock(&data->print_mutex);
                pthread_mutex_unlock(&data->philos[i].meal_mutex);
                return NULL;
            }
            
            // Check meal completion
            if (data->num_meals > 0 && data->philos[i].meals_eaten < data->num_meals)
                all_full = false;
            
            pthread_mutex_unlock(&data->philos[i].meal_mutex);
            i++;
        }
        
        // Check if all philosophers have eaten enough
        if (data->num_meals > 0 && all_full)
        {
            pthread_mutex_lock(&data->sim_mutex);
            data->sim_end = true;
            pthread_mutex_unlock(&data->sim_mutex);
            return NULL;
        }
        
        // Sleep to reduce CPU usage
        usleep(1000);
    }
    return NULL;
}

void start_simulation(t_data *data)
{
    int i;
    pthread_t monitor_thread;
    
    // Create philosopher threads
    i = -1;
    while (++i < data->num_philos)
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
    
    // Create monitor thread
    pthread_create(&monitor_thread, NULL, monitor_routine, data);
    
    // Join philosopher threads
    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, NULL);
    
    // Join monitor thread
    pthread_join(monitor_thread, NULL);
}


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


void precise_sleep(int ms)
{
    long start = get_time_ms();
    long now;
    
    while (1)
    {
        now = get_time_ms();
        if (now - start >= ms)
            break;
        usleep(500);
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

// Add these functions
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