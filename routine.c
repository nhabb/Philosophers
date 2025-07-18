#include "philo.h"


void assign_fork(t_philo *philo,t_mutex *first_fork,t_mutex *second_fork)
{
    if (philo->id % 2 == 0) 
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    } 
    else 
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
}

void *philo_routine(void *arg)
{
    t_philo *philo;
    t_mutex *first_fork;
    t_mutex *second_fork;
    
    philo = (t_philo *)arg;
    if (philo->id % 2 == 0) 
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    } 
    else 
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    // assign_fork(philo,first_fork,second_fork);
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
            pthread_mutex_unlock(second_fork);
            pthread_mutex_unlock(first_fork);
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
        
        // Release forks (reverse order)
        pthread_mutex_unlock(second_fork);
        pthread_mutex_unlock(first_fork);
        
        // Check if simulation ended after eating
        if (simulation_ended(philo->data))
            break;
            
        // Sleep
        print_status(philo, "is sleeping");
        precise_sleep(philo->data->time_to_sleep);
        
        // Check if simulation ended after sleeping
        if (simulation_ended(philo->data))
            break;
            
        // Think
        print_status(philo, "is thinking");
        
        // Add adaptive delay to prevent starvation
        if (philo->data->num_philos % 2 == 1) {
            long think_start = get_time_ms();
            long think_time;
            while (!simulation_ended(philo->data)) {
                think_time = get_time_ms() - think_start;
                // Break if we've thought long enough
                if (think_time >= philo->data->time_to_eat / 2) 
                    break;
                usleep(100);
            }
        }
    }
    return NULL;
}

void start_simulation(t_data *data)
{
    int i;
    pthread_t monitor_thread;

    data->start_time = get_time_ms();
    i = -1;
    while (++i < data->num_philos) {
        data->philos[i].last_meal = data->start_time;
    }
    i = -1;
    while (++i < data->num_philos)
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
    pthread_create(&monitor_thread, NULL, monitor_routine, data);
    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, NULL);
    pthread_join(monitor_thread, NULL);
}
