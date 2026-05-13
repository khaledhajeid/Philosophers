#include "philo.h"

static int	check_death(t_philo *philo)
{
	long	time_since_meal;

	pthread_mutex_lock(&philo->meal_lock);
	time_since_meal = get_time_ms() - philo->last_meal_time;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_since_meal >= philo->data->time_to_die)
		return (1);
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	finished_eating;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	finished_eating = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_lock(&data->philos[i].meal_lock);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			finished_eating++;
		pthread_mutex_unlock(&data->philos[i].meal_lock);
		i++;
	}
	if (finished_eating == data->philo_count)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (check_death(&data->philos[i]))
			{
				pthread_mutex_lock(&data->state_lock);
				data->sim_stop = 1;
				pthread_mutex_unlock(&data->state_lock);
				pthread_mutex_lock(&data->write_lock);
				printf("%ld %d died\n",
					get_time_ms() - data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->write_lock);
				return (NULL);
			}
		}
		if (check_all_ate(data))
		{
			pthread_mutex_lock(&data->state_lock);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->state_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}