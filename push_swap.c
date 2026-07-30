/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/30 14:08:50 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

	char	**get_flags(void)
{
	static char	*flags[6] = {
		"",
		"--simple",
		"--medium",
		"--complex",
		"--adaptive",
		"--bench"
	};

	return (flags);
}
int search_flag(char *av)
{
	int	i;
	
	i = 0;
	if (!av)
		return((0));
	while (i < 6)
	{
		if (ft_strcmp((get_flags()[i]), av))
			return (i);
		i++;
	}
	return (0);
}

int is_dup(t_stack *a, int n)
{
	t_node *current_node;

	current_node = a->head;
	while (current_node)
	{
		if(current_node->number == n)
			print_error();
		else
			current_node = current_node->next;
	}
	return (1);
}
void add_to_stack(char *p_str, t_stack *a)
{
	t_node *new_node;

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
}

int add_and_search(char *parsed_str, t_stack *a, t_state *config)
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
int	parser(int ac, char **av, t_stack *a, t_state *config)
{
	char **parsed_str;
	int i;
	int k;

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

t_stack *init_stack (void)
{
	t_stack *stack;
	
	stack = malloc(sizeof(t_stack));
		if (!stack)
			return NULL;
	stack->size = 0;
	stack->tail = NULL;
	stack->head = NULL;
	return (stack);
}

t_state *init_config(void)
{
	t_state *config;

	config = malloc(sizeof(t_state));
	config->strategy = 0;
	config->bench_mode = 0;
	config->total_flags = 0;
	config->a = NULL;
	config->b = NULL;
	config->bench = NULL;
	config->print_mode = 0;
	config->total_elements = 0;
	return (config);
	
}

float get_disorder(t_stack *a)
/** 
Low disorder: if disorder < 0.2, your chosen method must run in O(n2) time.
Medium disorder: if 0.2 ≤ disorder < 0.5, your chosen method must run in
O(n√n) time.
High disorder: if disorder ≥ 0.5, your chosen method must run in O(n log n)
time
**/
{
	t_node	*i;
	t_node	*j;
	float mistakes;
	float total_pairs;
	total_pairs = (a->size * (a->size - 1) / 2);
	mistakes = 0;
	i = a->head;
	if ((a->size) <= 1)
		return (0.0);
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->number > j->number)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	return ((mistakes / total_pairs));
}

int	main(int ac, char **av)
{
	t_stack *a;
	t_stack *b;
	t_state *config;
	t_node *current;

	a = init_stack();
	b = init_stack();
	config = init_config();
	config->a = a;
	config->b = b;
	parser(ac, av, a, config);	
	int final_disorder = ((get_disorder(a)) * 10000);
	if (config->bench_mode)
		ft_printf("[bench] disorder: %d,%d%%\n", (final_disorder / 100),
	(final_disorder % 100));
	ft_printf("estrategia: %d", config->strategy);
	selection_sort(config, 0, NULL);
	current = malloc(sizeof(t_bench));
	current = a->head;
	while (current)
	{
		ft_printf("\n%d", current->number);
		current = current->next;
	}
	free(current);
	free(a);
}

