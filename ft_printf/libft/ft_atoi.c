/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 08:15:46 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/05/26 11:02:32 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	is_negative;
	int	result;

	i = 0;
	is_negative = 0;
	while ((nptr[i] == 32) || ((nptr[i] >= 9) && (nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			is_negative = 1;
		i++;
	}
	result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result = ((result * 10) + (nptr[i] - '0'));
		i++;
	}
	if (is_negative)
		result = result * -1;
	return (result);
}
