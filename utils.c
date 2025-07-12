#include "philo.h"

bool	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		return (LONG_MAX);
	if (*str == '+')
		str++;
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		if (result > INT_MAX)
			return (LONG_MAX);
		str++;
	}
	return (result * sign);
}

// bool	simulation_ended(t_data *data)
// {
// 	bool	ended;

// 	mutex_lock(&data->sim_mutex);
// 	ended = data->sim_end;
// 	mutex_unlock(&data->sim_mutex);
// 	return (ended);
// }