/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:30:45 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/05 16:57:47 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long	ft_intcount(long n)
{
	int	digits_total;

	digits_total = 0;
	if (n <= 0)
		digits_total++;
	while (n != 0)
	{
		n = n / 10;
		digits_total++;
	}
	return (digits_total);
}

char	*ft_itoa(int n)
{
	char	*c;
	int		t;
	int		last;
	long	nbr;

	nbr = n;
	t = (ft_intcount(n) - 1);
	last = t;
	c = (char *)ft_calloc((ft_intcount(nbr) + 1), (sizeof(char)));
	if (!c)
		return (NULL);
	if (nbr < 0)
	{
		nbr = (nbr * -1);
		c[0] = '-';
	}
	while (t >= 0 && c[t] != '-')
	{
		c[t] = ((nbr % 10) + '0');
		nbr = (nbr / 10);
		t--;
	}
	c[last + 1] = '\0';
	return (c);
}
