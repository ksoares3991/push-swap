/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:03:20 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 14:36:23 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_dup(t_stack *a, int n, t_state *config, char **f_str)
{
	t_node	*current_node;

	current_node = a->head;
	while (current_node)
	{
		if (current_node->number == n)
			print_error(a, config, f_str);
		current_node = current_node->next;
	}
	return (0);
}

void	add_to_stack(char *p_str, t_stack *a, t_state *config, char **f_str)
{
	t_node	*new_node;

	is_dup(a, ft_atol(p_str), config, f_str);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		print_error(a, config, f_str);
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
		a->tail->next = new_node;
		a->tail = new_node;
	}
	a->size++;
	
}

int	add_and_search(char *str, t_stack *a, t_state *config, char **f_str)
{
	if (ft_isnumber(str, a, config, f_str))
	{
		add_to_stack(str, a, config, f_str);
		return (1);
	}
	if (search_flag(str) && search_flag(str) < 5)
	{
		if (f_str[1] != NULL)
			print_error(a, config, f_str);
		config->total_flags++;
		config->strategy = search_flag(str);
		return (1);
	}
	if (search_flag(str) && search_flag(str) == 5)
	{
		if (f_str[1] != NULL)
			print_error(a, config, f_str);
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
		if (!av[i] || av[i][0] == '\0')
			print_error(a, config, NULL);
		k = 0;
		parsed_str = ft_split(av[i], ' ');
		if (!parsed_str || !parsed_str[0])
			print_error(a, config, parsed_str);
		while (parsed_str[k])
		{
			add_and_search(parsed_str[k], a, config, parsed_str);
			k++;
		}
		free_parsed_str(parsed_str);
		i++;
		if ((config->bench_mode > 1) || config->total_flags > 1)
			print_error(a, config, NULL);
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
