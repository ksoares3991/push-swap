/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:54:21 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/26 13:43:11 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

int	print_char(va_list *args)
{
	char	c;

	c = (char)va_arg(*args, int);
	return (write(1, &c, 1));
}

int	print_str(va_list *args)
{
	char	*s;
	int		len;

	s = va_arg(*args, char *);
	if (!s)
		s = "(null)";
	len = (ft_strlen(s));
	return (write(1, s, len));
}

int	print_pct(va_list *args)
{
	(void)args;
	return (write(1, "%", 1));
}
