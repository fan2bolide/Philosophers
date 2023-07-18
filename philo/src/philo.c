#include "philo.h"
#include "philo_time.h"

void	*philo_start(void *param)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)param;
	pthread_mutex_lock(&philo->info->start_philos_mutex);
	pthread_mutex_unlock(&philo->info->start_philos_mutex);
	pthread_mutex_lock(&philo->death_time_mutex);
	philo->death_time = get_current_time();
	pthread_mutex_lock(&philo->start_time_mutex);
	philo->start_time = philo->death_time;
	pthread_mutex_unlock(&philo->start_time_mutex);
	timeval_add_ms(&philo->death_time, philo->info->time_to_die);
	pthread_mutex_unlock(&philo->death_time_mutex);
	printf("%llu %d is thinking\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
	if (philo->id % 2 == 1)
		usleep(philo->info->time_to_eat * 500);
	if (philo->info->number_of_meals_needed == 0)
	{
		while (1)
		{
			philo_eat(philo);
			pthread_mutex_lock(&philo->start_time_mutex);
			printf("%llu %d is sleeping\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
			pthread_mutex_unlock(&philo->start_time_mutex);
			philo_sleep(philo);
			printf("%llu %d is thinking\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
			usleep(100);
		}
	}
	else
	{
		while (i < philo->info->number_of_meals_needed)
		{
			philo_eat(philo);
			printf("%llu %d is sleeping\n", get_timestamp(philo->philos, get_current_time()), philo->id + 1);
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
	pthread_mutex_lock(&philos->info->start_philos_mutex);
	while (i < philos->info->nb_of_philos)
	{
		philos[i].id = i;
		philos[i].philos = philos;
		philos[i].info = philos->info;
		pthread_mutex_init(&philos[i].fork, NULL);
		pthread_mutex_init(&philos[i].death_time_mutex, NULL);
		pthread_mutex_init(&philos[i].start_time_mutex, NULL);
		pthread_create(&philos[i].philo, NULL, philo_start, &philos[i]);
		i++;
	}
	pthread_mutex_unlock(&philos->info->start_philos_mutex);

}

void	create_monitor(t_philo *philos)
{
	pthread_t monitor;
	pthread_create(&monitor, NULL, start_monitor, philos);
	pthread_join(monitor, NULL);
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
	create_monitor(philos);
	join_philos(philos);
	return (0);
}
