#include "philo.h"

void	clean_exit(t_data *data)
{
	int	i;

	if (data->forks)
	{
		i = -1;
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->forks[i]);
		free(data->forks);
	}
	if (data->philos)
	{
		i = -1;
		while (++i < data->philo_count)
			pthread_mutex_destroy(&data->philos[i].meal_lock);
		free(data->philos);
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->state_lock);
}

static void	assign_forks(t_philo *philo, t_data *data, int i)
{
	int	fork_1;
	int	fork_2;

	fork_1 = i;
	fork_2 = (i + 1) % data->philo_count;
	if (fork_1 < fork_2)
	{
		philo->first_fork = &data->forks[fork_1];
		philo->second_fork = &data->forks[fork_2];
	}
	else
	{
		philo->first_fork = &data->forks[fork_2];
		philo->second_fork = &data->forks[fork_1];
	}
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		if (pthread_mutex_init(&data->philos[i].meal_lock, NULL) != 0)
			return (0);
		assign_forks(&data->philos[i], data, i);
		i++;
	}
	return (1);
}

int	init_data(t_data *data)
{
	int	i;

	data->sim_stop = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->state_lock, NULL) != 0)
		return (0);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (init_philos(data));
}
