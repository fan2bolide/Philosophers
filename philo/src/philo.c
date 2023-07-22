/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bajeanno <bajeanno@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:33:48 by bajeanno          #+#    #+#             */
/*   Updated: 2023/07/20 16:33:49 by bajeanno         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos->info->start_philos_mutex);
	while (i < philos->info->nb_of_philos)
	{
		philos[i].id = i;
		philos[i].philos = philos;
		philos[i].info = philos->info;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].timing_mutex, NULL);
		pthread_create(&philos[i].philo, NULL, philo_start, &philos[i]);
		i++;
	}
	pthread_mutex_unlock(&philos->info->start_philos_mutex);
}

void	destroy_philos(t_philo *philos)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&philos->info->start_philos_mutex);
	while (i < philos->info->nb_of_philos)
	{
		pthread_mutex_destroy(&philos[i].timing_mutex);
		pthread_mutex_destroy(&philos[i].fork);
		pthread_detach(philos[i].philo);
		i++;
	}
}

void	create_monitor(t_philo *philos)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, start_monitor, philos);
	pthread_join(monitor, NULL);
}

void	join_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->nb_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_philo_info	info;
	int				nb_of_philos;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1)
		return (1);
	nb_of_philos = ft_atoi(argv[1]);
	philos = malloc(sizeof (t_philo) * nb_of_philos);
	info.nb_of_philos = nb_of_philos;
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	info.finished_eating = 0;
	info.a_philo_is_dead = 0;
	info.number_of_meals_needed = 0;
	if (argv[5])
		info.number_of_meals_needed = ft_atoi(argv[5]);
	philos->info = &info;
	pthread_mutex_init(&philos->info->start_philos_mutex, NULL);
	pthread_mutex_init(&philos->info->dead_philo_mutex, NULL);
	pthread_mutex_init(&info.finished_eating_mutex, NULL);
	create_philos(philos);
	ft_usleep(50000);
	create_monitor(philos);
	join_philos(philos);
	pthread_mutex_destroy(&philos->info->dead_philo_mutex);
	pthread_mutex_destroy(&philos->info->finished_eating_mutex);
	return (free(philos), 0);
}
