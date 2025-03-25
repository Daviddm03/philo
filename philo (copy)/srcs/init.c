/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:16:22 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/25 12:07:23 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	signal;

	i = 0;
	res = 0;
	signal = 1;

	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + str[i++] - '0';
	return (res * signal);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((s1[i]) || (s2[i])) && (i < n))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/* void	init_each_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philo[i].id = i + 1;
		table->philo[i].table = table;
		table->philo[i].meals = 0;
		table->philo[i].full = 0;
		table->philo[i].is_eating = 0;
		table->philo[i].death_deadline = ft_get_time() + table->time_to_die;
		table->philo[i].rfork = &table->forks[i];
		if (table->philo_num == i + 1)
			table->philo[i].lfork = &table->forks[0];
		else
			table->philo[i].lfork = &table->forks[i + 1];
		i++;
	}
} */

void init_each_philo(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_num)
    {
        table->philo[i].id = i + 1;
        table->philo[i].table = table;
        table->philo[i].meals = 0;
        table->philo[i].full = 0;
        table->philo[i].is_eating = 0;
        table->philo[i].death_deadline = ft_get_time() + table->time_to_die;
        table->philo[i].rfork = &table->forks[i];
        if (table->philo_num == i + 1)
            table->philo[i].lfork = &table->forks[0];
        else
            table->philo[i].lfork = &table->forks[i + 1];
        i++;
    }
}

int	init_mutexes(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (fork_mutex_error(table, i));
		i++;
	}
	i = 0;
	while (i < table->philo_num)
	{
		if (pthread_mutex_init(&table->philo[i].philo_mutex, NULL))
			return (philo_mutex_error(table, i));
		i++;
	}
	if (pthread_mutex_init(&table->table_mutex, NULL))
		return (table_mutex_error(table, 1));
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (table_mutex_error(table, 2));
	return (1);
}

int	init_philo(t_table *table)
{
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (philo_error("Error: Allocation for the forks!\n", table));
	table->philo = malloc(sizeof(t_philo) * table->philo_num);
	//table->philo = malloc(table->philo_num * sizeof(*(table->philo)));
	if (!table->philo)
		return (philo_error("Error: Allocation for the philo's!\n", table));
	init_each_philo(table);
	if (!init_mutexes(table))
		return (philo_error("Error: Mutex init!\n", table));
	return (1);
}
