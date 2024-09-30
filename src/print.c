/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:21:08 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 16:36:05 by fzayani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_handle_format(const char *format, int *i, va_list args)
{
	int	stock;

	stock = 0;
	if (format[*i + 1] == 'l' && \
		(format[*i + 2] == 'd' || format[*i + 2] == 'i'))
	{
		stock += ft_putnbr_printf(va_arg(args, long));
		*i += 2;
	}
	else
	{
		stock += ft_check_format(format[*i + 1], args);
		(*i)++;
	}
	return (stock);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		stock;
	va_list	args;

	i = 0;
	stock = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			stock += ft_handle_format(format, &i, args);
		else
			stock += ft_putchar_printf(format[i]);
		i++;
	}
	va_end(args);
	return (stock);
}
