/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:46:55 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/02/25 20:10:40 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int main(int ac, char **av)
{
	t_table	table;

	if(!init_input(ac, av, &table))
		return (0);
	if (!init_philo(&table))
		return (0);
	if (!init_dinner(&table))
		return (0);
	free_table(&table);
}
