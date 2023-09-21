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

static void	parse_arguments(char **argv, t_philo_info *info)
{
	info->nb_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	info->finished_eating = 0;
	info->a_philo_is_dead = 0;
	info->number_of_meals_needed = 0;
	if (argv[5])
		info->number_of_meals_needed = ft_atoi(argv[5]);
}

static int	init_mutexes(pthread_mutex_t *mutex1, \
						pthread_mutex_t *mutex2, \
						pthread_mutex_t *mutex3)
{
	if (pthread_mutex_init(mutex1, NULL))
		return (1);
	if (pthread_mutex_init(mutex2, NULL))
		return (pthread_mutex_destroy(mutex2), 1);
	if (pthread_mutex_init(mutex3, NULL))
		return (pthread_mutex_destroy(mutex2), \
				pthread_mutex_destroy(mutex3), 1);
	return (0);
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
	parse_arguments(argv, &info);
	philos->info = &info;
	if (init_mutexes(&philos->info->start_philos_mutex, \
	&philos->info->end_simulation_mutex, \
	&info.finished_eating_mutex))
		return (free(philos), 1);
	create_philos(philos);
	usleep(50000);
	create_monitor(philos);
	destroy_philos(philos);
	pthread_mutex_destroy(&philos->info->end_simulation_mutex);
	pthread_mutex_destroy(&philos->info->finished_eating_mutex);
	return (free(philos), 0);
}
