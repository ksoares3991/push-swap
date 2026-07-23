/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 16:44:04 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/23 18:59:52 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

int	print_char(va_list *args);
int	ft_printf(const char *format, ...);
int	print_str(va_list *args);
int	print_pct(va_list *args);
int	print_hex_lc(va_list *args);
int	print_base(unsigned long n, char *base, unsigned long b_len);
int	print_hex_uc(va_list *args);
int	print_nbr_unsigned(va_list *args);
int	print_ptr(va_list *args);
int	print_nbr(long n);
int	print_nbr_signed(va_list *args);

#endif