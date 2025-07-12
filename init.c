#include "philo.h"

bool	init_data(t_data *data)
{
	int	i;

	data->start_time = get_time_ms();
	data->sim_end = false;
	mutex_init(&data->sim_mutex);
	mutex_init(&data->print_mutex);
	data->forks = malloc(sizeof(t_mutex) * data->num_philos);
	if (!data->forks)
		return (false);
	i = -1;
	while (++i < data->num_philos)
		mutex_init(&data->forks[i]);
	if (!init_philos(data))
	{
		free(data->forks);
		return (false);
	}
	return (true);
}

bool	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (false);
	i = -1;
	while (++i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal = data->start_time;
		mutex_init(&data->philos[i].meal_mutex);
		data->philos[i].data = data;
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->num_philos - 1)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
	}
	return (true);
}