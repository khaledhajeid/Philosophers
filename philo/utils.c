#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	check_simulation_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_lock);
	stop = data->sim_stop;
	pthread_mutex_unlock(&data->state_lock);
	return (stop);
}

void	ft_msleep(long time_to_sleep, t_data *data)
{
	long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < time_to_sleep)
	{
		if (check_simulation_stop(data))
			break ;
		usleep(500);
	}
}

void	print_status(t_philo *philo, char *status)
{
	long	time;

	pthread_mutex_lock(&philo->data->write_lock);
	if (!check_simulation_stop(philo->data))
	{
		time = get_time_ms() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, status);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}