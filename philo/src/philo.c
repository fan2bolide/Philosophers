#include "philo.h"

void	start_philo(t_philo philo)
{
	
}

void create_philos(t_philo *philos)
{
	int i;

	i = 0;
	while (i < philos[i].nb_of_philos)
	{
		philos[i].nb_of_philos = philos[0].nb_of_philos;
		philos[i].time_to_die = philos[0].time_to_die;
		philos[i].time_to_eat = philos[0].time_to_eat;
		philos[i].time_to_eat = philos[0].time_to_eat;
		philos[i].time_to_eat = philos[0].time_to_eat;

		pthread_create(philos[i], NULL, start_philo);
	}
}

int main(int argc, char **argv)
{
	t_philo *philos;

	if (argc < 5 || argc > 6)
		return (1);
	philos = malloc(sizeof (pthread_t) * nb_of_philos);
	philo.nb_of_philos = ft_atoi(argv[1]);

	return (0);
}
