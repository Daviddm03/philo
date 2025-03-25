/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddias-mo <ddias-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:05:33 by ddias-mo          #+#    #+#             */
/*   Updated: 2025/03/25 12:53:55 by ddias-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	hold(t_philo *philo)
{
    if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->lfork);
		display_status(FORKS, philo);
		pthread_mutex_lock(philo->rfork);
		display_status(FORKS, philo);
	}
	else
	{
		pthread_mutex_lock(philo->rfork);
		display_status(FORKS, philo);
		pthread_mutex_lock(philo->lfork);
		display_status(FORKS, philo);		
	}
}

/* void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->philo_mutex);
	display_status(EAT, philo);
	new_sleep(philo, philo->table);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->philo_mutex);
} */

void	eat(t_philo *philo)
{
	size_t start;
	
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->philo_mutex);
	
	display_status(EAT, philo);
	
	// Use a simpler sleep method for eating
	start = ft_get_time();
	while ((ft_get_time() - start < (size_t)philo->table->time_to_eat) && is_philo_alive(philo->table))
		new_sleep(philo->table->time_to_eat, philo, philo->table);
	pthread_mutex_lock(&philo->philo_mutex);
	philo->is_eating = 0;
	philo->death_deadline = ft_get_time() + philo->table->time_to_die;
	pthread_mutex_unlock(&philo->philo_mutex);
}

void	drop(t_philo *philo)
{
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}