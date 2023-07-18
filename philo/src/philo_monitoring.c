#include "philo.h"

void *start_monitor(void *param)
{
	t_philo *philos = param;
	int i;

	i = 0;
	usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&philos[i].death_time_mutex);
		if (timeval_compare(philos[i].death_time, get_current_time()) <= 0)
		{
			pthread_mutex_unlock(&philos[i].death_time_mutex);
			pthread_mutex_lock(&philos->info->dead_philo_mutex);
			philos->info->a_philo_is_dead = 1;
			printf("%llu %d died\n", get_timestamp(philos, get_current_time()), i + 1);
			pthread_mutex_destroy(&philos->info->start_philos_mutex);
			i = 0;
			while (i < philos->info->nb_of_philos)
			{
				pthread_mutex_destroy(&philos[i].death_time_mutex);
				pthread_mutex_destroy(&philos[i].start_time_mutex);
				pthread_detach(philos[i].philo);
				i++;
			}
			pthread_mutex_unlock(&philos->info->dead_philo_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philos[i].death_time_mutex);
		i++;
		if (i >= philos->info->nb_of_philos)
			i = 0;
		usleep(100);
	}
}