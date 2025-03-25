/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:25:36 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/25 12:50:35 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

# define EAT "is eating"
# define FORKS "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

typedef struct s_philo
{
    pthread_t			td;
	int					id;
	pthread_mutex_t		*lfork;
	pthread_mutex_t		*rfork;
	pthread_mutex_t		philo_mutex;
	struct	s_table		*table;
	size_t				death_deadline;
	int					meals;
	int					full;
	int					is_eating;
	
}              t_philo;

typedef struct s_table
{
	long				philo_num;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				repeat;
	int					live;
	int					thread_created;
	int					thread_error;
	int					is_dinner_active;
	int					full_philos;
	size_t				init_time;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_t			watchdog;
	pthread_mutex_t		table_mutex;
	pthread_mutex_t		print_mutex;
	
}			t_table;

size_t	ft_get_time(void);

long	ft_atoi(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		wait_threads(t_table *table);
int		is_philo_full(t_philo *philo);
int		is_philo_alive(t_table *table);
int		dinner(t_table *table);
int		thread_error(t_table *table);
int		philo_error(char *msg, t_table *table);
int		one_philo(t_table *table);
int		init_input(int ac, char **av, t_table *table);
int		fork_mutex_error(t_table *table, int n);
int		philo_mutex_error(t_table *table, int n);
int		table_mutex_error(t_table *table, int flag);
int		init_philo(t_table *table);
int		init_dinner(t_table *table);

void	init_each_philo(t_table *table);
void	display_status(char *str, t_philo *philo);
void	ms_sleep(size_t milliseconds, t_table *table);
void	new_sleep(size_t milliseconds, t_philo *philo, t_table *table);
void	hold(t_philo *philo);
void	eat(t_philo *philo);
void	drop(t_philo *philo);
void	*monitor(void *arg);
void	end_dinner(t_table *table);
void	free_table(t_table *table);

#endif