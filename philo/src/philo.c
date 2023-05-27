#include "philo.h"

void	*philo_start(void *param)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)param;
	if (philo->info->number_of_meals_needed == 0)
	{
		while (1)
		{
			if (!philo_eat(philo))
				return (NULL);
			printf("philo %d is sleeping\n", philo->id);
			philo_sleep(philo);
			usleep(100);
		}
	}
	else
	{
		while (i < philo->info->number_of_meals_needed)
		{
			philo_eat(philo);
			printf("philo %d is sleeping\n", philo->id);
			philo_sleep(philo);
			usleep(100);
			i++;
		}
	}
	return (NULL);
}

void	create_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->info->nb_of_philos)
	{
		philos[i].id = i;
		philos[i].philos = philos;
		philos[i].info = philos->info;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_create(&philos[i].philo, NULL, philo_start, &philos[i]);
		i++;
	}
}

void	join_philos(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos->info->nb_of_philos)
	{
		pthread_join(philos[i].philo, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_philo_info info;
	int		nb_of_philos;

	(void)argc;
	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1)
		return (1);
	nb_of_philos = ft_atoi(argv[1]);
	philos = malloc(sizeof (t_philo) * nb_of_philos);
	info.nb_of_philos = nb_of_philos;
	info.time_to_die = ft_atoi(argv[2]);
	info.time_to_eat = ft_atoi(argv[3]);
	info.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info.number_of_meals_needed = ft_atoi(argv[5]);
	else
		info.number_of_meals_needed = 0;
	philos->info = &info;
	create_philos(philos);
	join_philos(philos);
	return (0);
}
