/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:42:00 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 16:51:34 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	is_positive(const char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0')
	{
		ft_printf("Error : Empty string\n");
		return (0);
	}
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			ft_printf("Error : Non-digit character\n");
			return (0);
		}
		i++;
	}
	if (atol(s) <= 0)
		return (0);
	return (1);
}

// int	init_arg(int argc, char **argv, t_table *table)
// {
// 	int	i;

// 	i = 1;
// 	if (argc < 5)
// 		return (ft_printf("%s", MSG), 0);
// 	while (i < argc)
// 	{
// 		if (!is_positive(argv[i]))
// 			return (ft_printf("%s", ERROR), 0);
// 		i++;
// 	}
// 	table->num_philo = atoi(argv[1]);
// 	table->t2_die = atol(argv[2]);
// 	table->t2_eat = atol(argv[3]);
// 	table->t2_sleep = atol(argv[4]);
// 	table->meals_required = (argc == 6) ? atoi(argv[5]) : -1;
// 	table->all_ate_enough = 0;
// 	table->philos_full = 0;
// 	table->philo = malloc(sizeof(t_philo) * table->num_philo);
// 	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
// 	if (!table->philo || !table->forks)
// 		return (write(2, "Memory allocation failure\n", 26), 0);
// 	return (1);
// }

int	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5)
	{
		ft_printf("%s", MSG);
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		if (!is_positive(argv[i]))
		{
			ft_printf("%s", ERROR);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_memory(t_table *table)
{
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (!table->philo || !table->forks)
	{
		write(2, "Memory allocation failure\n", 26);
		return (0);
	}
	return (1);
}

int	init_arg(int argc, char **argv, t_table *table)
{
	if (!validate_args(argc, argv))
		return (0);
	table->num_philo = atoi(argv[1]);
	table->t2_die = atol(argv[2]);
	table->t2_eat = atol(argv[3]);
	table->t2_sleep = atol(argv[4]);
	if (argc == 6)
		table->meals_required = atoi(argv[5]);
	else
		table->meals_required = -1;
	table->all_ate_enough = 0;
	table->philos_full = 0;
	if (!init_memory(table))
		return (0);
	return (1);
}
