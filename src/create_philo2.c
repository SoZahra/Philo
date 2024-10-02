/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 17:33:41 by fzayani           #+#    #+#             */
/*   Updated: 2024/10/02 14:26:58 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	wait_to_start(t_philo *philo) 
{
	pthread_mutex_lock(&philo->table->start_mutex);
	while (!philo->table->can_start)
	{
		pthread_mutex_unlock(&philo->table->start_mutex);
		usleep(100);
		pthread_mutex_lock(&philo->table->start_mutex);
	}
	pthread_mutex_unlock(&philo->table->start_mutex);
}

int	check_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->is_dead || table->all_ate_enough)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

void	sleep_and_think(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->table->t2_sleep, philo->table);
	print_status(philo, "is thinking");
	usleep(500);
}

void	check_and_print_simulation_end(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->all_ate_enough)
		ft_printf("All philosophers have eaten\
			%d times. Simulation completed successfully.\n",
			table->meals_required);
	else if (table->is_dead)
		ft_printf("A philosopher has died. Simulation ended.\n");
	pthread_mutex_unlock(&table->death_mutex);
}

int	check_all_ate_enough(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->all_ate_enough)
	{
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}
