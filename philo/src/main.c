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

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	str_contains_digits_only(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_arguments(char **argv, t_philo_info *info)
{
	if (!str_contains_digits_only(argv[1]) \
	|| !str_contains_digits_only(argv[2]) \
	|| !str_contains_digits_only(argv[3]) \
	|| !str_contains_digits_only(argv[4]))
		return (-1);
	info->nb_of_philos = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (info->nb_of_philos <= 0 || info->time_to_die <= 0 \
	|| info->time_to_eat <= 0 || info->time_to_sleep <= 0)
		return (-1);
	info->finished_eating = 0;
	info->a_philo_is_dead = 0;
	info->number_of_meals_needed = 0;
	if (argv[5])
	{
		if (!str_contains_digits_only(argv[5]))
			return (-1);
		info->number_of_meals_needed = ft_atoi(argv[5]);
	}
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
	if (!philos)
		return (1);
	if (parse_arguments(argv, &info) < 0)
	{
		write(2, "Philosophers : Bad arguments.\n", 30);
		free(philos);
		return (1);
	}
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
