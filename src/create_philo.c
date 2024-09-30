/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:57:51 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 14:21:40 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


u_int64_t get_current_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000);
}

u_int64_t get_times(u_int64_t start_time) {
    return get_current_time() - start_time;
}

void ft_usleep(int microseconds, t_table *table)
{
    u_int64_t start_time;

    start_time = get_current_time(); // Capture du temps actuel

    // Tant que la durée écoulée n'a pas atteint ou dépassé la durée voulue
    while ((int)(get_current_time() - start_time) <= microseconds)
    {
        pthread_mutex_lock(&table->death_mutex);
        if (table->is_dead == 1)
        {
            pthread_mutex_unlock(&table->death_mutex);
            break;
        }
        pthread_mutex_unlock(&table->death_mutex);
        usleep(100);
    }
}

void *philo_lifecycle(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    pthread_mutex_lock(&philo->table->start_mutex);
    while (!philo->table->can_start)
    {
        pthread_mutex_unlock(&philo->table->start_mutex);
        usleep(100);
        pthread_mutex_lock(&philo->table->start_mutex);
    }
    pthread_mutex_unlock(&philo->table->start_mutex);
    while (1)
    {
        pthread_mutex_lock(&philo->table->death_mutex);
        if (philo->table->is_dead)
        {
            pthread_mutex_unlock(&philo->table->death_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->table->death_mutex);
        if (philo->table->meals_required != -1 && philo->time_eaten >= philo->table->meals_required)
        {
            pthread_mutex_lock(&philo->table->death_mutex);
            philo->table->philos_full++;
            if (philo->table->philos_full == philo->table->num_philo)
                philo->table->all_ate_enough = 1;
            pthread_mutex_unlock(&philo->table->death_mutex);
            break;
        }
        take_forks(philo);
        eat(philo);
        release_forks(philo);
        print_status(philo, "is sleeping");
        ft_usleep(philo->table->t2_sleep, philo->table);
        print_status(philo, "is thinking");
        usleep(500);
    }
    return NULL;
}

void print_status(t_philo *philo, const char *status)
{
    pthread_mutex_lock(&philo->table->death_mutex);
    if (!philo->table->is_dead)
        ft_printf("%ld %d %s\n", get_times(philo->table->start_time), philo->id + 1, status);
    pthread_mutex_unlock(&philo->table->death_mutex);
}

void start_one(t_table *table)
{
     if(table->num_philo == 1)
    {
        pthread_create(&table->philo[0].thread, NULL, philo_lifecycle_one, &table->philo[0]);
        table->can_start = 1;
        // pthread_mutex_unlock(&table->start_mutex);
        pthread_join(table->philo[0].thread, NULL);
        return;
    }
}


void start_simu(t_table *table)
{
    int i;
    pthread_t monitor_thread;

    table->start_time = get_current_time();
    table->is_dead = 0;
    table->all_ate_enough = 0;
    table->philos_full = 0;
    table->can_start = 0;
    i = 0;
    start_one(table);
    while (i < table->num_philo)
    {
        table->philo[i].last_meal = table->start_time;
        pthread_create(&table->philo[i].thread, NULL, philo_lifecycle, &table->philo[i]);
        i++;
    }
    pthread_mutex_lock(&table->start_mutex);
    table->can_start = 1;
    pthread_mutex_unlock(&table->start_mutex);
    pthread_create(&monitor_thread, NULL, monitor_philo, table);
    i = 0;
    while (i < table->num_philo)
    {
        pthread_join(table->philo[i].thread, NULL);
        i++;
    }
    pthread_join(monitor_thread, NULL);
    if (!table->is_dead && table->all_ate_enough)
        ft_printf("All philosophers have eaten %d times. Simulation completed successfully.\n", table->meals_required);
}

void *monitor_philo(void *arg)
{
    t_table *table = (t_table *)arg;
    int i;
    long time_since_last_meal;

    while (1)
    {
		i = 0;
        while (i < table->num_philo)
        {
            pthread_mutex_lock(&table->philo[i].meal_mutex);
            time_since_last_meal = get_current_time() - table->philo[i].last_meal;
            pthread_mutex_unlock(&table->philo[i].meal_mutex);
            if (time_since_last_meal >= table->t2_die)
            {
                if (table->philo[i].time_eaten < table->meals_required || table->meals_required == -1)
                {
                    pthread_mutex_lock(&table->death_mutex);
                    if (!table->is_dead)
                    {
                        table->is_dead = 1;
                        ft_printf("%ld Philo %d died\n", get_times(table->start_time), table->philo[i].id + 1);
                    }
                    pthread_mutex_unlock(&table->death_mutex);
                    return NULL;
                }
            }
			i++;
        }
        pthread_mutex_lock(&table->death_mutex);
        if (table->all_ate_enough)
        {
            pthread_mutex_unlock(&table->death_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&table->death_mutex);
        usleep(50); // Check more frequently
    }
}
