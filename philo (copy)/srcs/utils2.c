/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:00:30 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/19 18:20:32 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	wait_threads(t_table *table)
{
	while (1)
	{
		pthread_mutex_lock(&table->table_mutex);
		if (table->thread_error)
			return (0);
		if (table->thread_created)
		{
			pthread_mutex_unlock(&table->table_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->table_mutex);
		usleep(1);
	}
	return (1);
}

int	dinner(t_table *table)
{
	int	dinner;

	pthread_mutex_lock(&table->table_mutex);
	if(table->is_dinner_active == 0)
		dinner = 0;
	else
		dinner = 1;
	pthread_mutex_unlock(&table->table_mutex);
	return (dinner);	
}

int	philo_error(char *msg, t_table *table)
{
	printf("%s", msg);
	if (table)
		free (table->philo);
	if (table)
		free (table->forks);
	return (0);
}

void end_dinner(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	table->is_dinner_active = 0;
	pthread_mutex_unlock(&table->table_mutex);
}

void	free_table(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	free(table->philo);
	free(table->forks);
}