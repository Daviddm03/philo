/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:50:01 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/19 18:24:58 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_number(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 0;
		if (av[i][0] == 0)
			return (0);
		while (av[i][j])
		{
			if (av[i][0] == '-' && j == 0)
				j++;
			if (av[i][j] > '9' || av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_overflow(t_table *table)
{
	if (table->philo_num < 1)
		return (philo_error("Error: Must have at least 1 philosopher!\n", NULL));
	if (table->time_to_die <= 0 || table->time_to_die <= 0 || table->time_to_sleep <= 0)
		return (philo_error("Error: Argument less than 1!\n", NULL));
	if (table->philo_num > LONG_MAX || table->repeat > LONG_MAX || table->time_to_die > LONG_MAX
		|| table->time_to_eat > LONG_MAX || table->time_to_sleep > LONG_MAX)
		return (philo_error("Error: Argument is greater than 2147483647!\n", NULL));
	return (1);
}

int	init_table(char **av, t_table *table)
{
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->live = 1;
	table->is_dinner_active = 1;
	table->thread_created = 0;
	table->thread_error = 0;
	table->full_philos = 0;
	if (av[5] && ft_atoi(av[5]) > 0)
		table->repeat = ft_atoi(av[5]);
	else if (!av[5])
		table->repeat = -1;
	else
		return (philo_error("Error: Argument less than 1!\n", NULL));
	if (!check_overflow(table))
		return (0);
	return (1);
}

int	init_input(int ac, char **av, t_table *table)
{
	if (ac != 5 && ac != 6)
		return (philo_error("Error: Invalid number of arguments!\n", NULL));
	if (!is_number(ac, av))
		return (philo_error("Error: Arguments must be number!\n", NULL));
	if (!init_table(av, table))
		return (0);
	return (1);
}
