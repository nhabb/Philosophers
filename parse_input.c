#include "philo.h"

bool	parse_args(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atol(argv[5]);
	else
		data->num_meals = -1;
	
	if (data->num_philos <= 0 || data->time_to_die < 60 
        || data->time_to_eat < 60 ||
		data->time_to_sleep < 60 || (argc == 6 && data->num_meals <= 0))
	{
		printf("Invalid arguments\n");
		return (false);
	}
	return (true);
}