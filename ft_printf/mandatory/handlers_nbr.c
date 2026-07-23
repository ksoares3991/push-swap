/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 15:15:47 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/25 15:07:47 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	print_base(unsigned long n, char *base, unsigned long b_len)
{
	int	count;

	count = 0;
	if (n >= b_len)
		count += print_base(n / b_len, base, b_len);
	count += write(1, &base[n % b_len], 1);
	return (count);
}

int	print_ptr(va_list *args)
{
	unsigned long	addr;
	int				count;

	count = 0;
	addr = (unsigned long)va_arg(*args, void *);
	if (!addr)
		return (write(1, "(nil)", 5));
	count += write(1, "0x", 2);
	count += print_base(addr, "0123456789abcdef", 16);
	return (count);
}

int	print_nbr(long nb)
{
	int		count;

	count = 0;
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		count += print_nbr(nb / 10);
	count ++;
	ft_putchar_fd((nb % 10) + '0', 1);
	return (count);
}

int	print_nbr_unsigned(va_list *args)
{
	return (print_base(va_arg(*args, unsigned int), "0123456789", 10));
}

int	print_nbr_signed(va_list *args)
{
	return (print_nbr(va_arg(*args, int)));
}
