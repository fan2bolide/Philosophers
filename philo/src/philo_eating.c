#include "philo.h"
#include "philo_time.h"

void	philo_eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%lld philo %d has taken a fork\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
		pthread_mutex_lock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
		printf("%lld philo %d has taken a fork\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
	}
	else
	{
		pthread_mutex_lock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
		printf("%lld philo %d has taken a fork\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
		pthread_mutex_lock(&philo->fork);
		printf("%lld philo %d has taken a fork\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
	}
	printf("philo %d is eating\n", philo->id + 1);
	pthread_mutex_lock(&philo->death_time_mutex);
	philo->death_time = get_current_time();
	timeval_add_ms(&philo->death_time, philo->info->time_to_die);
	pthread_mutex_unlock(&philo->death_time_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&(philo->philos[(philo->id + 1) % philo->info->nb_of_philos]).fork);
}