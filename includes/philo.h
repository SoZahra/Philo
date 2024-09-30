/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:38 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 14:54:54 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG \
	"Usage: ./philo number_of_philosophers\
 time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_table	t_table;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	int					time_eaten;
	int					meals_eaten;
	int					start_time;
	int					time_to_eat;
	long				last_meal;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		meal_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	int					num_philo;
	int					t2_die;
	int					t2_eat;
	int					t2_sleep;
	int					t2_think;
	long				start_time;
	int					all_ate_enough;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		start_mutex;
	t_philo				*philo;
	int					is_dead;
	int					min_meals;
	int					can_start;
	int					philos_full;
	int					meals_required;
}						t_table;

// create_philo///

void					init_philo(t_table *table);
void					init_forks(t_table *table);
void					*philo_lifecycle(void *arg);
void					start_simu(t_table *table);
void					*monitor_philo(void *arg);
void					init_table(t_table *table);
void					print_status(t_philo *philo, const char *status);

//// main

u_int64_t				get_current_time(void);
u_int64_t				get_times(u_int64_t start_time);
void					ft_usleep(int microseconds, t_table *table);

/// one_philo

void					*philo_lifecycle_one(void *arg);

////utils

void					cleanup(t_table *table);
u_int64_t				get_time(void);
// int						error(const char *message, void *unused);
// int						ft_printf(const char *format, ...);
void					ft_is_digit(long long nbr, int base, int *len);
// void					ft_putstr(char *str, int *len);
int	ft_putchar_printf(char c);
//

int						ft_putstr_printf(const char *str);
int						ft_putnbr_printf(long nb);
int						ft_printf(const char *format, ...);

/// take

void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
int						sleep_and_think(t_philo *philo);
int						check_death(t_philo *philo);
void					release_forks(t_philo *philo);

/// init

void					init_philo(t_table *table);
void					init_table(t_table *table);
void					init_forks(t_table *table);
void					init_simu(t_table *table);

/// check  argc

int						is_positive(const char *s);
int						ft_isdigit(int c);
int						init_arg(int argc, char **argv, t_table *table);

#endif