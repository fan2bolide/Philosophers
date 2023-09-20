/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:46 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:47 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_routine(t_philo *philo);

static void	init_timings(t_philo *philo)
{
	pthread_mutex_lock(&philo->timing_mutex);
	philo->start_time = get_current_time();
	philo->death_time = get_current_time();
	timeval_add_ms(&philo->death_time, philo->info->time_to_die);
	pthread_mutex_unlock(&philo->timing_mutex);
}

void	*philo_start(void *param)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->info->start_philos_mutex);
	pthread_mutex_unlock(&philo->info->start_philos_mutex);
	init_timings(philo);
	printf("0 %d is thinking\n", philo->id + 1);
	if (philo->id % 2 == 1)
		ft_usleep(philo->info->time_to_eat * 500, philo);
	if (philo->info->number_of_meals_needed == 0)
		i = -1;
	while (i < philo->info->number_of_meals_needed)
	{
		if (philo_routine(philo) < 0)
			return (NULL);
		i++;
		if (philo->info->number_of_meals_needed == 0)
			i = -1;
	}
	pthread_mutex_lock(&philo->info->finished_eating_mutex);
	philo->info->finished_eating++;
	pthread_mutex_unlock(&philo->info->finished_eating_mutex);
	return (NULL);
}

int	philo_routine(t_philo *philo)
{
	if (philo_eat(philo) < 0)
		return (-1);
	if (philo_print(philo, "is sleeping") < 0)
		return (-1);
	philo_sleep(philo);
	if (philo_print(philo, "is thinking") < 0)
		return (-1);
	usleep(100);
	return (0);
}
