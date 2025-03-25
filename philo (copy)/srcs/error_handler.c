/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:03:04 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/02/25 20:10:06 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	thread_error(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	table->thread_error = 1;
	pthread_mutex_unlock(&table->table_mutex);
	return (philo_error("Erro: Thread created.\n", table));
}

int	fork_mutex_error(t_table *table, int n)
{
	int i;

	i = 0;
	while (i <= n)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	return (0);
}

int	philo_mutex_error(t_table *table, int n)
{
	int i;

	i = 0;
	fork_mutex_error(table, table->philo_num - 1);
	while (i <= n)
	{
		pthread_mutex_destroy(&table->philo[i].philo_mutex);
		i++;
	}
	return (0);
}

int	table_mutex_error(t_table *table, int flag)
{
	philo_mutex_error(table, table->philo_num - 1);
	if (flag == 1 || flag == 2)
		pthread_mutex_destroy(&table->table_mutex);
	if (flag == 2)
		pthread_mutex_destroy(&table->print_mutex);
	return (0);
}