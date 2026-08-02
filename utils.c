/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:14 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/02 13:06:35 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_error(t_stack *a, t_state *config, char **f_str)
{
	if (a)
		free_stack(a);
	if (config)
	{
		if (config->b)
			free_stack(config->b);
		free(config);
	}
	if (f_str)
		free_parsed_str(f_str);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

int	is_int(long n, t_stack *a, t_state *config, char **f_str)
{
	if (n > 2147483647 || n < -2147483648)
		print_error(a, config, f_str);
	return (1);
}

int	ft_isnumber(char *s, t_stack *a, t_state *config, char **f_str)
{
	long	i;

	i = 0;
	if (search_flag(s))
		return (0);
	if (!s || s[0] == '\0')
		print_error(a, config, f_str);
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		print_error(a, config, f_str);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			print_error(a, config, f_str);
		i++;
	}
	is_int(ft_atol(s), a, config, f_str);
	return (1);
}

long	ft_atol(char *s)
{
	long	i;
	long	result;
	int		is_negative;

	is_negative = 0;
	i = 0;
	result = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			is_negative = 1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	if (is_negative)
		return (-result);
	return (result);
}

int	ft_strcmp(const char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

void	free_parsed_str(char **f_str)
{
	int	i;

	i = 0;
	if (!f_str)
		return ;
	while (f_str[i])
	{
		free(f_str[i]);
		i++;
	}
	free(f_str);
}

void	free_stack(t_stack *stack)
{
	t_node	*tmp;

	if (!stack)
		return ;
	while (stack->head)
	{
		tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
	free(stack);
}