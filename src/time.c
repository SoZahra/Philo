/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:58:34 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 16:58:46 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

u_int64_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (u_int64_t)1000 + (tv.tv_usec / 1000));
}

u_int64_t	get_times(u_int64_t start_time)
{
	return (get_current_time() - start_time);
}

void	ft_usleep(int microseconds, t_table *table)
{
	u_int64_t	start_time;

	start_time = get_current_time();
	while ((int)(get_current_time() - start_time) <= microseconds)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (table->is_dead == 1)
		{
			pthread_mutex_unlock(&table->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(100);
	}
}
