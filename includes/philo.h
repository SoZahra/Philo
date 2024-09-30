/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:38 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 18:02:04 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG "Usage: ./philo number_of_philosophers\
 time_to_die time_to_eat time_to_sleep\
 [number_of_times_each_philosopher_must_eat]\n"

# define ERROR "Error: All arguments must be positive numbers greater than 0.\n"

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

/// create_philo2

void					wait_to_start(t_philo *philo);
int						check_simulation_end(t_table *table);
void					sleep_and_think(t_philo *philo);
void					check_and_print_simulation_end(t_table *table);
int						check_all_ate_enough(t_table *table);

//// main

u_int64_t				get_current_time(void);
u_int64_t				get_times(u_int64_t start_time);
void					ft_usleep(int microseconds, t_table *table);

/// one_philo

void					*philo_lifecycle_one(void *arg);
void					start_one(t_table *table);

////utils

void					cleanup(t_table *table);
u_int64_t				get_time(void);

/// take

void					take_forks(t_philo *philo);
void					eat(t_philo *philo);
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

/// print

int						ft_handle_format(const char *format, int *i,
							va_list args);
int						ft_printf(const char *format, ...);

/// print_utils

void					ft_is_digit(long long nbr, int base, int *len);
int						ft_putstr_printf(const char *str);
int						ft_putnbr_printf(long nb);
int						ft_putchar_printf(char c);
int						ft_check_format(char str, va_list args);

#endif