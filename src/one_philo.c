/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:22:17 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 14:33:42 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_lifecycle_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->table->is_dead)
	{
		philo->table->is_dead = 1;
		pthread_mutex_lock(philo->l_fork);
		ft_printf("(%ld)	Philosophe %d has taken a fork\n", \
				get_times(philo->table->start_time), philo->id + 1);
		pthread_mutex_unlock(philo->l_fork);
		usleep(philo->table->t2_die * 1000);
		ft_printf("(%ld)	Philosophe %d has died\n", \
				get_times(philo->table->start_time), philo->id + 1);
	}
	return (NULL);
}
