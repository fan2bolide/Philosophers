/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:48 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:49 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	stop_creating_philos(t_philo *philos, int nb_philos)
{
	int	i;

	i = 0;
	philos->info->a_philo_is_dead = 1;
	pthread_mutex_unlock(&philos->info->end_simulation_mutex);
	pthread_mutex_unlock(&philos->info->start_philos_mutex);
	while (i < nb_philos)
	{
		pthread_join(philos[i].philo, NULL);
		pthread_mutex_destroy(&philos[i].timing_mutex);
		i++;
	}
	i = 0;
	while (i < nb_philos)
		pthread_mutex_destroy(&philos[i++].fork);
	pthread_mutex_destroy(&philos->info->start_philos_mutex);
	pthread_mutex_destroy(&philos->info->end_simulation_mutex);
	pthread_mutex_destroy(&philos->info->finished_eating_mutex);
}

int	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos->info->start_philos_mutex);
	while (i < philos->info->nb_of_philos)
	{
		philos[i].id = i;
		philos[i].philos = philos;
		philos[i].info = philos->info;
		if (pthread_mutex_init(&philos[i].fork, NULL))
			return (philos->info->a_philo_is_dead = 1, \
			pthread_mutex_unlock(&philos->info->end_simulation_mutex), 1);
		if (pthread_mutex_init(&philos[i].timing_mutex, NULL))
			return (philos->info->a_philo_is_dead = 1, \
			pthread_mutex_unlock(&philos->info->end_simulation_mutex), 1);
		pthread_mutex_lock(&philos->info->end_simulation_mutex);
		if (pthread_create(&philos[i].philo, NULL, philo_start, &philos[i]))
			return (stop_creating_philos(philos, i), 1);
		pthread_mutex_unlock(&philos->info->end_simulation_mutex);
		i++;
	}
	pthread_mutex_unlock(&philos->info->start_philos_mutex);
	return (0);
}

void	destroy_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->nb_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		pthread_mutex_destroy(&philos[i].timing_mutex);
		i++;
	}
	i = 0;
	while (i < philos->info->nb_of_philos)
		pthread_mutex_destroy(&philos[i++].fork);
	pthread_mutex_destroy(&philos->info->start_philos_mutex);
	pthread_mutex_destroy(&philos->info->end_simulation_mutex);
	pthread_mutex_destroy(&philos->info->finished_eating_mutex);
}

void	create_monitor(t_philo *philos)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, start_monitor, philos))
	{
		pthread_mutex_lock(&philos->info->end_simulation_mutex);
		philos->info->a_philo_is_dead = 1;
		pthread_mutex_unlock(&philos->info->end_simulation_mutex);
		write(2, \
		"Philosophers : thread monitoring cannot launch, aborting.\n", 58);
		return ;
	}
	pthread_join(monitor, NULL);
}
