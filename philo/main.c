#include "philo.h"

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_atoi_strict(const char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (-1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		res = (res * 10) + (str[i] - '0');
		if (res > 2147483647)
			return (-1);
		i++;
	}
	return ((int)res);
}

int	parse_args(t_data *data, int argc, char **argv)
{
	data->philo_count = ft_atoi_strict(argv[1]);
	data->time_to_die = ft_atoi_strict(argv[2]);
	data->time_to_eat = ft_atoi_strict(argv[3]);
	data->time_to_sleep = ft_atoi_strict(argv[4]);
	if (data->philo_count <= 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0)
		return (0);
	if (argc == 6)
	{
		data->must_eat_count = ft_atoi_strict(argv[5]);
		if (data->must_eat_count <= 0)
			return (0);
	}
	else
		data->must_eat_count = -1;
	return (1);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	data->start_time = get_time_ms();
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].last_meal_time = data->start_time;
		if (pthread_create(&data->philos[i].thread, NULL,
				&philo_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, &monitor_routine, data) != 0)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	memset(&data, 0, sizeof(t_data));
	if (!parse_args(&data, argc, argv))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (!init_data(&data))
		return (1);
	if (!start_simulation(&data))
		return (1);
	clean_exit(&data);
	return (0);
}