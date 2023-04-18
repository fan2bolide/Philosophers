#include "philo.h"

void philo_sleep(t_philo *philo)
{
	usleep(philo->time_to_sleep);
}