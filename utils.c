/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:14 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/29 18:56:36 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int is_int(long n)
{
	if(n > 2147483647 || n < -2147483648)
		{
			ft_putstr_fd("Error\n", 2);
			exit(1);
		}
	return (1);
}
void print_error()
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}
int ft_isnumber(char *s)
{
    long i;

    i = 0;
	(void)s;
    if (!s || s[0] == '\0')
    	print_error();
    if (s[i] == '-')
        i++;
    if (!s[i])
        print_error();
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            print_error();
        i++;
    }
    if (!is_int(ft_atol(s)))
        print_error();

    return (1);
}

long	ft_atol (char *s)
{
	long	i;
	long	result;
	int		is_negative;

	is_negative = 0;
	i = 0;
	while ((s[i] == 32) || ((s[i] >= 9) && (s[i] <= 13)))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			is_negative = 1;
		i++;
	}
	result = 0;
	while (ft_isdigit(s[i]))
	{
		result = ((result * 10) + (s[i] - '0'));
		i++;
	}
	if (is_negative)
		result = result * -1;
	return (result);
}

int ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i])||(s2[i]))
	{
		if ((s1[i]) != (s2[i]))
			return (0);
		else if ((s1[i]) == (s2[i]) && ((s1[i + 1]) || (s2[i + 1])))
			i++;
		else if ((s1[i]) == (s2[i]) && (!s1[i + 1]) == (!s2[i + 1]))
			return (1);
	}
	return (0);
}
// int ft_isaflag(char *av)
// {
// 	int	i;

// 	i = 0;
	
// }