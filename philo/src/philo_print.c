/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:53 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:54 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->info->dead_philo_mutex);
	if (philo->info->a_philo_is_dead == 0)
	{
		pthread_mutex_lock(&philo->timing_mutex);
		printf("%llu %d %s\n", get_timestamp(philo->philos, \
		get_current_time()), philo->id + 1, message);
		pthread_mutex_unlock(&philo->timing_mutex);
	}
	pthread_mutex_unlock(&philo->info->dead_philo_mutex);
}
