#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

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

struct s_to_thread
{
	t_philo	*philos;
	t_philo *philo;
};

int		ft_atoi(const char *str);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
int		philo_eat(t_philo *philo);

#endif
