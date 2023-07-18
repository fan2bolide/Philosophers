#include "philo_time.h"

void ft_usleep(int time_in_us)
{
	struct timeval end_time;
	end_time = get_current_time();
	timeval_add_ms(&end_time, time_in_us / 1000);
	usleep(time_in_us / 2);
	while (timeval_compare(end_time, get_current_time()) >= 0)
		usleep(100);
}
