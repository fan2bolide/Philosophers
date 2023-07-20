/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:43 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:44 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"

#define NB_OF_USECONDS_IN_A_SECOND 1000000
#define NB_OF_USECONDS_IN_A_MILLISECOND 1000

struct timeval	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		current_time.tv_sec += current_time.tv_usec \
								/ NB_OF_USECONDS_IN_A_SECOND;
		current_time.tv_usec %= NB_OF_USECONDS_IN_A_SECOND;
	}
	return (current_time);
}

long long	get_timestamp(const t_philo *philosopher, \
							const struct timeval current_time)
{
	return ((current_time.tv_sec - philosopher->start_time.tv_sec)
		* (long long)NB_OF_USECONDS_IN_A_MILLISECOND
		+ (current_time.tv_usec - philosopher->start_time.tv_usec)
		/ NB_OF_USECONDS_IN_A_MILLISECOND);
}

struct timeval	*timeval_add_ms(struct timeval *tv, \
								const int number_of_ms_to_add)
{
	const unsigned long long	new_tv_usec = tv->tv_usec + \
			(number_of_ms_to_add * (long long)NB_OF_USECONDS_IN_A_MILLISECOND);

	if (new_tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		tv->tv_sec += new_tv_usec / NB_OF_USECONDS_IN_A_SECOND;
		tv->tv_usec = new_tv_usec % NB_OF_USECONDS_IN_A_SECOND;
	}
	else
		tv->tv_usec = new_tv_usec;
	return (tv);
}

int	timeval_compare(const struct timeval t1, const struct timeval t2)
{
	if (t1.tv_sec < t2.tv_sec)
		return (-1);
	if (t1.tv_sec > t2.tv_sec)
		return (1);
	if (t1.tv_usec < t2.tv_usec)
		return (-1);
	return (t1.tv_usec > t2.tv_usec);
}
