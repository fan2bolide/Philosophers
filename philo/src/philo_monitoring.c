#include "philo.h"
#include "philo_time.h"

void *start_monitor(void *param)
{
	t_philo *philos = param;
	int i;

	i = 0;
	while (i < philos->info->nb_of_philos)
	{
		if (timeval_compare(philos->death_time, get_current_time()) <= 0)
		{
			pthread_mutex_lock(&philos->info->dead_philo_mutex);
			philos->info->a_philo_is_dead = 1;
			pthread_mutex_unlock(&philos->info->dead_philo_mutex);
			printf("PHILO %d IS DEAD!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", i + 1);
			i = 0;
			while (i < philos->info->nb_of_philos)
			{
				pthread_detach(philos[i].philo);
				i++;
			}
			return (NULL);
		}
		i++;
	}
	return (NULL);
}