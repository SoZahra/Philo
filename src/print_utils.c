/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fzayani <fzayani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 16:35:03 by fzayani           #+#    #+#             */
/*   Updated: 2024/09/30 16:43:08 by fzayani          ###   ########.fr       */
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

int	ft_check_format(char str, va_list args)
{
	int	i;

	i = 0;
	if (str == 's')
		i += ft_putstr_printf(va_arg(args, char *));
	else if (str == 'd' || str == 'i')
		i += ft_putnbr_printf(va_arg(args, int));
	else if (str == 'l')
		return (0);
	else if (str == '%')
		i += ft_putchar_printf('%');
	return (i);
}
