#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	pthread_mutex_t	meal_lock;
	pthread_t		thread;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				sim_stop;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	state_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_data;


int		parse_args(t_data *data, int argc, char **argv);
void	clean_exit(t_data *data);

int		init_data(t_data *data);
int		init_philos(t_data *data);
int		start_simulation(t_data *data);

void	*philo_routine(void *arg);
void	philo_eat(t_philo *philo);
void	philo_sleep_think(t_philo *philo);

void	*monitor_routine(void *arg);
int		check_simulation_stop(t_data *data);

long	get_time_ms(void);
void	ft_msleep(long time_to_sleep, t_data *data);
void	print_status(t_philo *philo, char *status);

#endif