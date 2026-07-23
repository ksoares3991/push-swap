/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:03:18 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/26 14:05:49 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	ft_dispatch_table(char specifier, va_list *args)
{
	static int	(*handlers[256])(va_list *args);
	static int	init;

	if (!init)
	{
		handlers['c'] = print_char;
		handlers['s'] = print_str;
		handlers['%'] = print_pct;
		handlers['x'] = print_hex_lc;
		handlers['X'] = print_hex_uc;
		handlers['u'] = print_nbr_unsigned;
		handlers['p'] = print_ptr;
		handlers['i'] = print_nbr_signed;
		handlers['d'] = print_nbr_signed;
		init = 1;
	}	
	if (handlers[(unsigned char)specifier])
		return (handlers[(unsigned char)specifier](args));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start (args, format);
	count = 0;
	if (!format)
		return (-1);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			count += ft_dispatch_table(*format, &args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end (args);
	return (count);
}
