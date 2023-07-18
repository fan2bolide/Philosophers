#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define NB_OF_USECONDS_IN_A_SECOND 1000000
# define NB_OF_USECONDS_IN_A_MILLISECOND 1000

typedef struct s_philo_infos
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_of_philos;
	int	number_of_meals_needed;
	int a_philo_is_dead;
	pthread_mutex_t dead_philo_mutex;
	pthread_mutex_t start_philos_mutex;
}	t_philo_info;

typedef struct s_philo
{
	int				id;
	struct timeval	start_time;
	struct timeval	death_time;
	pthread_mutex_t	death_time_mutex;
	pthread_mutex_t	start_time_mutex;
	pthread_mutex_t	fork;
	pthread_t		philo;
	struct s_philo	*philos;
	t_philo_info	*info;
}	t_philo;


struct timeval	get_current_time(void);
long long		get_timestamp(const t_philo *philosopher,
							   const struct timeval current_time);
void			timeval_add_ms(struct timeval *tv, const int n);
int				timeval_compare(const struct timeval t1, \
								const struct timeval t2);
int				ft_atoi(const char *str);
void			philo_sleep(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_print(t_philo *philo, char *message);
void			*start_monitor(void *param);
void			ft_usleep(int time_in_us);

#endif
