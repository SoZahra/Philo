/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:58:54 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 16:07:49 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_putchar_printf(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_printf(const char *str)
{
	int	i;

	i = 0;
	if (str == 0)
		return (ft_putstr_printf("(null)"));
	while (str[i])
	{
		ft_putchar_printf(str[i]);
		i++;
	}
	return (i);
}

int	ft_putnbr_printf(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		i += ft_putchar_printf('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_putnbr_printf(nb / 10);
	}
	i += ft_putchar_printf((nb % 10) + '0');
	return (i);
}

void	ft_is_digit(long long nbr, int base, int *len)
{
	if (nbr < 0)
	{
		nbr *= -1;
		*len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_is_digit((nbr / base), base, len);
	*len += write(1, &"0123456789abcdef"[nbr % base], 1);
}

// int	ft_printf(const char *format, ...)
// {
// 	int		len;
// 	va_list	ptr;

// 	len = 0;
// 	va_start(ptr, format);
// 	while (*format)
// 	{
// 		if (*format != '%')
// 			len += write(1, format, 1);
// 		else if ((*format == '%') && *(format + 1))
// 		{
// 			format++;
// 			if (*format == 's')
// 				ft_putstr(va_arg(ptr, char *), &len);
// 			else if (*format == 'x')
// 				ft_is_digit((long long)va_arg(ptr, unsigned int), 16, &len);
// 			else if (*format == 'd')
// 				ft_is_digit((long long)va_arg(ptr, int), 10, &len);
// 			else if (*format == 'l' && *(format + 1) == 'd')
// 			{
// 				ft_is_digit(va_arg(ptr, long), 10, &len);
// 				format++;
// 			}
// 		}
// 		format++;
// 	}
// 	return (va_end(ptr), len);
// }

// static int	ft_check_format(char str, va_list args)
// {
// 	int	i;

// 	i = 0;
// 	if (str == 's')
// 		i += ft_putstr_printf(va_arg(args, char *));
// 	else if (str == 'd' || str == 'i')
// 		i += ft_putnbr_printf(va_arg(args, int));
// 	else if (str == 'l')
// 	{
// 		str = va_arg(args, int);
// 		if(str == 'd')
// 			i += ft_putnbr_printf(va_arg(args, long));
// 	}
// 	else if (str == '%')
// 		i += ft_putchar_printf('%');
// 	return (i);
// }

static int ft_check_format(char str, va_list args)
{
    int i = 0;

    if (str == 's')
        i += ft_putstr_printf(va_arg(args, char *));
    else if (str == 'd' || str == 'i')
        i += ft_putnbr_printf(va_arg(args, int));
    else if (str == 'l')
        return 0;
    else if (str == '%')
        i += ft_putchar_printf('%');

    return (i);
}

int ft_printf(const char *format, ...)
{
    int i = 0;
    int stock = 0;
    va_list args;

    if (!format)
        return (-1);

    va_start(args, format);
    while (format[i])
    {
        if (format[i] == '%')
        {
            if (format[i + 1] == 'l' && (format[i + 2] == 'd' || format[i + 2] == 'i'))
            {
                stock += ft_putnbr_printf(va_arg(args, long));
                i += 2;
            }
            else
            {
                stock += ft_check_format(format[i + 1], args);
                i++;
            }
        }
        else
        {
            stock += ft_putchar_printf(format[i]);
        }
        i++;
    }
    va_end(args);
    return (stock);
}

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		fprintf(stderr, "gettimeofday() FAILURE\n");
		return (0);
	}
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->start_mutex);
	free(table->philo);
	free(table->forks);
}
