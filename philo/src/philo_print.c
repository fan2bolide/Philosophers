#include "philo.h"

void philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->info->dead_philo_mutex);
	if (philo->info->a_philo_is_dead == 0)
	{
		pthread_mutex_lock(&philo->start_time_mutex);
		printf("%llu %d %s\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1, message);
		pthread_mutex_unlock(&philo->start_time_mutex);
	}
	pthread_mutex_unlock(&philo->info->dead_philo_mutex);
}
