/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:55 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:56 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*start_monitor(void *param)
{
	t_philo	*philos;
	int		i;

	philos = param;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&philos[i].timing_mutex);
		if (timeval_compare(philos[i].death_time, get_current_time()) <= 0)
		{
			pthread_mutex_unlock(&philos[i].timing_mutex);
			pthread_mutex_lock(&philos->info->dead_philo_mutex);
			philos->info->a_philo_is_dead = 1;
			printf("%llu %d died\n", get_timestamp(philos, \
			get_current_time()), i + 1);
			destroy_philos(philos);
			pthread_mutex_unlock(&philos->info->dead_philo_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philos[i].timing_mutex);
		i++;
		if (i >= philos->info->nb_of_philos)
			i = 0;
		usleep(100);
	}
}
