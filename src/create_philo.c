/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:57:51 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 17:56:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_philo_death(t_table *table, int i)
{
	long	time_since_last_meal;

	pthread_mutex_lock(&table->philo[i].meal_mutex);
	time_since_last_meal = get_current_time() - table->philo[i].last_meal;
	pthread_mutex_unlock(&table->philo[i].meal_mutex);
	if (time_since_last_meal >= table->t2_die)
	{
		if (table->philo[i].time_eaten < table->meals_required
			|| table->meals_required == -1)
		{
			pthread_mutex_lock(&table->death_mutex);
			if (!table->is_dead)
			{
				table->is_dead = 1;
				ft_printf("%ld Philo %d died\n", get_times(table->start_time),
					table->philo[i].id + 1);
			}
		}
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

void	*philo_lifecycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_to_start(philo);
	while (1)
	{
		if (check_simulation_end(philo->table))
			break ;
		pthread_mutex_lock(&philo->table->death_mutex);
		if (philo->table->meals_required != -1
			&& philo->time_eaten >= philo->table->meals_required)
		{
			philo->table->philos_full++;
			if (philo->table->philos_full == philo->table->num_philo)
				philo->table->all_ate_enough = 1;
			pthread_mutex_unlock(&philo->table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->death_mutex);
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	print_status(t_philo *philo, const char *status)
{
	pthread_mutex_lock(&philo->table->death_mutex);
	if (!philo->table->is_dead)
		ft_printf("%ld %d %s\n", get_times(philo->table->start_time), philo->id
			+ 1, status);
	pthread_mutex_unlock(&philo->table->death_mutex);
}

void	start_simu(t_table *table)
{
	int			i;
	pthread_t	monitor_thread;

	table->start_time = get_current_time();
	i = 0;
	start_one(table);
	while (i < table->num_philo)
	{
		table->philo[i].last_meal = table->start_time;
		pthread_create(&table->philo[i].thread, NULL, philo_lifecycle,
			&table->philo[i]);
		i++;
	}
	pthread_mutex_lock(&table->start_mutex);
	table->can_start = 1;
	pthread_mutex_unlock(&table->start_mutex);
	pthread_create(&monitor_thread, NULL, monitor_philo, table);
	i = -1;
	while (++i < table->num_philo)
		pthread_join(table->philo[i].thread, NULL);
	pthread_join(monitor_thread, NULL);
	if (!table->is_dead && table->all_ate_enough)
		ft_printf("All philosophers have eaten \
%d times. Simulation completed successfully.\n",
			table->meals_required);
}

void	*monitor_philo(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (check_philo_death(table, i))
				return (NULL);
			i++;
		}
		if (check_all_ate_enough(table))
			return (NULL);
		usleep(50);
	}
}

// void	*monitor_philo(void *arg)
// {
// 	t_table	*table;
// 	int		i;
// 	long	time_since_last_meal;

// 	table = (t_table *)arg;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < table->num_philo)
// 		{
// 			pthread_mutex_lock(&table->philo[i].meal_mutex);
// 			time_since_last_meal = get_current_time()
// 				- table->philo[i].last_meal;
// 			pthread_mutex_unlock(&table->philo[i].meal_mutex);
// 			if (time_since_last_meal >= table->t2_die)
// 			{
// 				if (table->philo[i].time_eaten < table->meals_required
// 					|| table->meals_required == -1)
// 				{
// 					pthread_mutex_lock(&table->death_mutex);
// 					if (!table->is_dead)
// 					{
// 						table->is_dead = 1;
// 						ft_printf("%ld Philo %d died\n",
// 							get_times(table->start_time), table->philo[i].id
// 							+ 1);
// 					}
// 					pthread_mutex_unlock(&table->death_mutex);
// 					return (NULL);
// 				}
// 			}
// 			i++;
// 		}
// 		pthread_mutex_lock(&table->death_mutex);
// 		if (table->all_ate_enough)
// 		{
// 			pthread_mutex_unlock(&table->death_mutex);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&table->death_mutex);
// 		usleep(50);
// 	}
// }
