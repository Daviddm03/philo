/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:02:54 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/25 12:59:10 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_get_time(void)
{
	struct	timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf ("Error: Get time of day.\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* void	display_status(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if(!ft_strncmp(str, "died", 4) && is_philo_alive(philo->table))
	{
		pthread_mutex_lock(&philo->table->table_mutex);
		time = ft_get_time() - philo->table->init_time;
		printf("%zu %i %s\n", time, philo->id, str);
		philo->table->live = 0;
		pthread_mutex_unlock(&philo->table->table_mutex);
	}
	else if (is_philo_alive(philo->table))
	{
		time = ft_get_time() - philo->table->init_time;
		printf("%zu %i %s\n", time, philo->id, str);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
} */

void	display_status(char *str, t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->table->print_mutex);
	if(!ft_strncmp(str, DIED, 4) && is_philo_alive(philo->table))
	{
		pthread_mutex_lock(&philo->table->table_mutex);
		time = ft_get_time() - philo->table->init_time;
		printf("%zu %i %s\n", time, philo->id, str);
		philo->table->live = 0;
		pthread_mutex_unlock(&philo->table->table_mutex);
	}
	else if (is_philo_alive(philo->table))
	{
		time = ft_get_time() - philo->table->init_time;
		printf("%zu %i %s\n", time, philo->id, str);
		fflush(stdout); // Ensure output is flushed immediately
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
}

int	is_philo_alive(t_table *table)
{
	int dead;

	pthread_mutex_lock(&table->table_mutex);
	if (!table->live)
		dead = 0;
	else
		dead = 1;
	pthread_mutex_unlock(&table->table_mutex);
	return (dead);
}

int	is_philo_full(t_philo *philo)
{
	int	full;

	pthread_mutex_lock(&philo->philo_mutex);
	if (!philo->full)
		full = 0;
	else
		full = 1;
	pthread_mutex_unlock(&philo->philo_mutex);
	return (full);
}

void	new_sleep(size_t milliseconds, t_philo *philo, t_table *table)
{
	size_t	start;
	size_t	now;

	start = ft_get_time();
	now = start;
	while ((now - start) < milliseconds && is_philo_alive(table))
	{
		pthread_mutex_lock(&philo->philo_mutex);
		if (ft_get_time() >= philo->death_deadline && philo->death_deadline != 0)
		{
			display_status(DIED, philo); // Mostra que o filósofo morreu
			pthread_mutex_lock(&table->table_mutex);
			table->live = 0;
			pthread_mutex_unlock(&table->table_mutex);
			pthread_mutex_unlock(&philo->philo_mutex);
			return;
		}
		pthread_mutex_unlock(&philo->philo_mutex);
		usleep(500); // Pequeno delay para evitar loop infinito
		now = ft_get_time();
	}
}
