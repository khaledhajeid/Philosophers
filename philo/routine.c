#include "philo.h"

static void	single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	ft_msleep(philo->data->time_to_die, philo->data);
	pthread_mutex_unlock(philo->first_fork);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->first_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
	ft_msleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	philo_sleep_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_msleep(philo->data->time_to_sleep, philo->data);
	print_status(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
	{
		single_philo_routine(philo);
		return (NULL);
	}
	while (!check_simulation_stop(philo->data))
	{
		philo_eat(philo);
		if (check_simulation_stop(philo->data))
			break ;
		philo_sleep_think(philo);
	}
	return (NULL);
}