/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:34:00 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:34:01 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int time_in_us, t_philo *philo)
{
	struct timeval	end_time;

	end_time = get_current_time();
	timeval_add_ms(&end_time, time_in_us / 1000);
	while (timeval_compare(end_time, get_current_time()) >= 0)
	{
		pthread_mutex_lock(&philo->info->end_simulation_mutex);
		if (philo->info->a_philo_is_dead != 0 || philo->info->finished_eating == philo->info->nb_of_philos)
			return ((void)pthread_mutex_unlock(&philo->info->end_simulation_mutex));
		pthread_mutex_unlock(&philo->info->end_simulation_mutex);
		usleep(1000);
	}
}
