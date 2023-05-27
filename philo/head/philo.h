#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo_infos
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_philos;
	int	number_of_meals_needed;
}	t_philo_info;

typedef struct s_philo
{
	int	id;
	pthread_mutex_t fork;
	pthread_t philo;
	struct s_philo *philos;
	t_philo_info *info;
}	t_philo;

int		ft_atoi(const char *str);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		philo_eat(t_philo *philo);

#endif
