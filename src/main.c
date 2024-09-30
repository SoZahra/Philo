/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:56:52 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 14:34:33 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_table table;
    // if (argc < 5) {
    //     ft_printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
    //     return 1;
    // }
    // t_table table;
    // table.num_philo = atoi(argv[1]);
    // table.t2_die = atol(argv[2]);
    // table.t2_eat = atol(argv[3]);
    // table.t2_sleep = atol(argv[4]);
    // table.meals_required = (argc == 6) ? atoi(argv[5]) : -1;
    // table.all_ate_enough = 0;
    // table.philos_full = 0;
    // table.philo = malloc(sizeof(t_philo) * table.num_philo);
    // table.forks = malloc(sizeof(pthread_mutex_t) * table.num_philo);
    // if (!table.philo || !table.forks) {
    //     // fprintf(stderr, "Memory allocation failure\n");
    //     write(2, "Memory allocation failure\n", 26);
    //     return 1;
    // }
    if(!init_arg(argc, argv, &table))
        return 1;
    init_simu(&table);
    start_simu(&table);
    cleanup(&table);
    return 0;
}
