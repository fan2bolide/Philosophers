#include "philo.h"

void philo_sleep(t_philo *philo)
{
	ft_usleep(philo->info->time_to_sleep * 1000);
}