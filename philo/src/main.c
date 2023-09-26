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

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_philo_info	info;
	int				nb_of_philos;

	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1)
		return (1);
	nb_of_philos = ft_atoi(argv[1]);
	philos = malloc(sizeof (t_philo) * nb_of_philos);
	if (!philos)
		return (0);
	parse_arguments(argv, &info);
	philos->info = &info;
	pthread_mutex_init(&philos->info->end_simulation_mutex, NULL);
	pthread_mutex_init(&philos->info->finished_eating_mutex, NULL);
	pthread_mutex_init(&philos->info->start_philos_mutex, NULL);
	create_philos(philos);
	usleep(50000);
	create_monitor(philos);
	destroy_philos(philos);
	return (free(philos), 0);
}
