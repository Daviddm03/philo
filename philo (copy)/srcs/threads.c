/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:03:18 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/25 12:52:33 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    try_to_eat(t_philo *philo)
{
	hold(philo); 
	eat(philo);
	drop(philo);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->meals++;
	//printf("Filósofo %d comeu %d vezes\n", philo->id, philo->meals);
	//fflush(stdout);
 	if (philo->meals == philo->table->repeat)
	{
		philo->full = 1;
		philo->death_deadline = 0;
	}
	else
    {
        philo->death_deadline = ft_get_time() + philo->table->time_to_die;
    }
	pthread_mutex_unlock(&philo->philo_mutex);
	display_status(SLEEP, philo);
	new_sleep(philo->table->time_to_sleep, philo, philo->table);
	display_status(THINK, philo);
}

void	*routine(void *table)
{
	t_philo	*philo;

	philo = (t_philo *)table;
	if(!wait_threads(philo->table))
		return (NULL);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->death_deadline = philo->table->time_to_die + ft_get_time();
	pthread_mutex_unlock(&philo->philo_mutex);
	display_status(THINK, philo);
	if (philo->id % 2 == 0)
		new_sleep(20, philo, philo->table);
	while (!is_philo_full(philo) && is_philo_alive(philo->table))
		try_to_eat(philo);
	return (NULL);
}

void	*monitor(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)arg;
	if (!wait_threads(table))
		return (NULL);
	while (dinner(table))
	{
		if (i == table->philo_num)
			i = 0;
		pthread_mutex_lock(&table->philo[i].philo_mutex);
		if (ft_get_time() >= table->philo[i].death_deadline
			&& table->philo[i].death_deadline != 0 && !table->philo[i].is_eating)
		{
			display_status(DIED, &table->philo[i]);
			pthread_mutex_unlock(&table->philo[i].philo_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->philo[i].philo_mutex);
		i++;
	}
	return (NULL);
}

int	init_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_create(&table->philo[i].td, NULL, &routine, &table->philo[i]))
			return (thread_error(table));
		i++;
	}
	pthread_mutex_lock(&table->table_mutex);
	table->thread_created = 1;
	pthread_mutex_unlock(&table->table_mutex);
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_join(table->philo[i].td, NULL))
			return (philo_error("Error: Thread join.\n", table));
		i++;
	}
	return (1);
}

int	init_dinner(t_table *table)
{
	if (table->philo_num == 1)
		return (one_philo(table));
	
	// Set the initialization time first
	table->init_time = ft_get_time();
	
	if (pthread_create(&table->watchdog, NULL, &monitor, table))
		return (philo_error("Error: Thread Monitoring!\n", table));
	
	if(!init_threads(table))
		return (0);
	end_dinner(table);
	if (!is_philo_alive(table))
		printf("Simulação encerrada em %zu ms\n", ft_get_time() - table->init_time);
	if (pthread_join(table->watchdog, NULL))
		return (philo_error("Error: Join monitoring!\n", table));
	
	return (1);
}
