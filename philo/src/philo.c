#include "philo.h"

void	*philo_start(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	philo_eat(philo);
	philo_sleep(philo);
	philo_think(philo);
	return (NULL);
}

void	create_philos(t_philo *philos)
{
	int					i;
	struct s_to_thread	pass_trough[philos[0].nb_of_philos];

	i = 0;
	while (i < philos[i].nb_of_philos)
	{
		philos[i].nb_of_philos = philos[0].nb_of_philos;
		philos[i].time_to_die = philos[0].time_to_die;
		philos[i].time_to_eat = philos[0].time_to_eat;
		philos[i].time_to_sleep = philos[0].time_to_sleep;
		pthread_create(&philos[i].philo, NULL, philo_start, &pass_trough[i]);
	}
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	int		nb_of_philos;

	(void)argc;
//	if (argc < 5 || argc > 6 || ft_atoi(argv[1]) < 1)
//		return (1);
	nb_of_philos = ft_atoi(argv[1]);
	philos = malloc(sizeof (pthread_t) * nb_of_philos);
	philos->nb_of_philos = nb_of_philos;
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	create_philos(philos);
	return (0);
}
