#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_philo
{
	int	nb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	id;
	int	number_of_times_each_philosopher_must_eat;
	pthread_t philo;

}	t_philo;

typedef struct s_table
{
	pthread_mutex_t *forks;
}	t_table;

int	ft_atoi(const char *str);

#endif
