/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_one.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:15:10 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/12 17:52:05 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void    *only_one(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    display_status(THINK, philo);
    pthread_mutex_lock(philo->rfork);
    display_status(FORKS, philo);
    pthread_mutex_unlock(philo->rfork);
    return (NULL);
}

int one_philo(t_table *table)
{
    table->init_time = ft_get_time();
    if (pthread_create(&table->watchdog, NULL, &monitor, table))
        return (philo_error("Error: Monitoring threads.\n", table));
    if(pthread_create(&table->philo[0].td, NULL, &only_one, &table->philo[0]))
        return (philo_error("Error: Philosophers threads!\n", table));
    pthread_mutex_lock(&table->table_mutex);
    table->thread_created = 1;
    pthread_mutex_unlock(&table->table_mutex);
    if (pthread_join(table->philo[0].td, NULL))
        return (philo_error("Error: Philosophers threads join!\n", table));
    while (1)
    {
        if (!is_philo_alive(table))
            break ;
        usleep(1);
    }
    if (pthread_join(table->watchdog, NULL))
        return (philo_error("Error: Monitoring join!\n", table));
    return (1);
}