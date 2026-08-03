/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:03:20 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 00:22:04 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_dup(t_stack *a, int n)
{
	t_node	*current_node;

	current_node = a->head;
	while (current_node)
	{
		if (current_node->number == n)
			print_error();
		else
			current_node = current_node->next;
	}
	return (1);
}

void	add_to_stack(char *p_str, t_stack *a)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->prev = a->tail;
	new_node->next = NULL;
	new_node->number = ft_atol(p_str);
	if (!a->head)
	{
		a->head = new_node;
		a->tail = new_node;
	}
	else
	{
		if (is_dup(a, ft_atol(p_str)))
		{
			a->tail->next = new_node;
			a->tail = new_node;
		}
	}
	a->size++;
	a->total_elements++;
}

int	add_and_search(char *parsed_str, t_stack *a, t_state *config)
{
	if (ft_isnumber(parsed_str))
	{
		add_to_stack(parsed_str, a);
		return (1);
	}
	if (search_flag(parsed_str) && search_flag(parsed_str) < 5)
	{
		config->total_flags++;
		config->strategy = search_flag(parsed_str);
		return (1);
	}
	if (search_flag(parsed_str) && search_flag(parsed_str) == 5)
	{
		config->bench_mode++;
		return (1);
	}
	return (1);
}

int	parse_and_stack(int ac, char **av, t_stack *a, t_state *config)
{
	char	**parsed_str;
	int		i;
	int		k;

	i = 1;
	while (i < ac)
	{
		if (!av[i])
			exit(1);
		k = 0;
		parsed_str = ft_split(av[i], ' ');
		while (parsed_str && parsed_str[k])
		{
			add_and_search(parsed_str[k], a, config);
			k++;
		}
		i++;
		if ((config->bench_mode > 1) || config->total_flags > 1)
		{
			print_error_debug(config);
			print_error();
		}
	}
	return (1);
}
