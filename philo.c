#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_meals]\n", argv[0]);
		return (1);
	}
	if (!parse_args(&data, argc, argv))
		return (1);
	if (!init_data(&data))
		return (1);
	start_simulation(&data);
	cleanup_data(&data);
	return (0);
}