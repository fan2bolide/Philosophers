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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->philos[(philo->id + 1) \
										% philo->info->nb_of_philos]).fork);
	philo_print(philo, "has taken a fork");
	philo_print(philo, "is eating");
	pthread_mutex_lock(&philo->timing_mutex);
	philo->death_time = get_current_time();
	timeval_add_ms(&philo->death_time, philo->info->time_to_die);
	pthread_mutex_unlock(&philo->timing_mutex);
	ft_usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&(philo->philos[(philo->id + 1) \
										% philo->info->nb_of_philos]).fork);
}
