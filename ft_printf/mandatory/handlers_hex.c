/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:54:00 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/23 12:55:05 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	print_hex_lc(va_list *args)
{
	return (print_base(va_arg(*args, unsigned int), "0123456789abcdef", 16));
}

int	print_hex_uc(va_list *args)
{
	return (print_base(va_arg(*args, unsigned int), "0123456789ABCDEF", 16));
}
