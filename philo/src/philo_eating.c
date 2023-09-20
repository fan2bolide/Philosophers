/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eating.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:58 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:59 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	left_fork = &philo->fork;
	right_fork = &(philo->philos[(philo->id + 1) \
					% philo->info->nb_of_philos]).fork;
	pthread_mutex_lock(left_fork);
	if (philo_print(philo, "has taken a fork") < 0)
		return (pthread_mutex_unlock(left_fork), -1);
	pthread_mutex_lock(right_fork);
	if (philo_print(philo, "has taken a fork") < 0)
		return (pthread_mutex_unlock(left_fork), \
			pthread_mutex_unlock(right_fork), -1);
	if (philo_print(philo, "is eating") < 0)
		return (pthread_mutex_unlock(left_fork), \
			pthread_mutex_unlock(right_fork), -1);
	pthread_mutex_lock(&philo->timing_mutex);
	philo->death_time = get_current_time();
	timeval_add_ms(&philo->death_time, philo->info->time_to_die);
	pthread_mutex_unlock(&philo->timing_mutex);
	ft_usleep(philo->info->time_to_eat * 1000, philo);
	pthread_mutex_unlock(left_fork);
	pthread_mutex_unlock(right_fork);
	return (0);
}
