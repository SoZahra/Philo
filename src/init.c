/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:32:08 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 11:44:26 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philo[i].id = i;
		table->philo[i].time_eaten = 0;
		table->philo[i].last_meal = get_current_time();
		table->philo[i].table = table;
		table->philo[i].l_fork = &table->forks[i];
		table->philo[i].r_fork = &table->forks[(i + 1) % table->num_philo];
		pthread_mutex_init(&table->philo[i].meal_mutex, NULL);
		i++;
	}
}

void init_table(t_table *table)
{
	pthread_mutex_init(&table->death_mutex, NULL);
	int i;

	i = 0;
	while(i < table->num_philo)
		i++;
	table->is_dead = 0;
	table->start_time = get_current_time();
}

void	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void init_simu(t_table *table)
{
	init_table(table);
    init_forks(table);
    init_philo(table);
}