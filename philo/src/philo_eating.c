#include "philo.h"

int	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a fork\n", philo->id);
		pthread_mutex_lock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
		printf("philo %d has taken a fork\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
		printf("philo %d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->fork);
		printf("philo %d has taken a fork\n", philo->id);
	}
	printf("philo %d is eating\n", philo->id);
	//update death time
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
	return (1);
}