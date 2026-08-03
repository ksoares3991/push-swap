/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/02 23:28:57 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

float	get_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	float	mistakes;
	float	total_pairs;

	if (a->size <= 1)
		return (0.0);
	total_pairs = (float)(a->size * (a->size - 1) / 2);
	mistakes = 0;
	i = a->head;
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
	return (mistakes / total_pairs);
}

static void	adaptive_select(t_state *config, t_stack *a, float disorder)
{
	if (!a || a->size <= 1 || is_sorted(a))
		return ;
	if (a->size == 2)
	{
		order_two(config);
		return ;
	}
	if (a->size == 3)
	{
		order_three(config);
		return ;
	}
	if (a->size == 5)
		selection_sort(config);
	else if ((!config->strategy && disorder < 0.2) || config->strategy == 1)
		selection_sort(config);
	else if ((!config->strategy && disorder >= 0.2 && disorder < 0.5)
		|| config->strategy == 2)
		ft_printf("MEDIUM PLACEHOLDER\n");
	else if ((!config->strategy && disorder >= 0.5) || config->strategy == 3)
		ft_printf("COMPLEX PLACEHOLDER ADAPTATIVO\n");
}

void	select_algorithm(t_state *config, t_stack *a)
{
	float	initial_disorder;

	initial_disorder = get_disorder(a);
	if (config->bench_mode)
		config->print_mode++;
	if (!config->strategy || config->strategy == 4)
		adaptive_select(config, a, initial_disorder);
	else if (config->strategy == 1)
		selection_sort(config);
	else if (config->strategy == 2)
		medium_sort(config);
	else if (config->strategy == 3)
		ft_printf("COMPLEX PLACEHOLDER SELECT ALGO\n");
	if (config->bench_mode)
		print_bench(config, initial_disorder);
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_state	*config;

	if (ac < 2)
		return (0);
	a = init_stack();
	b = init_stack();
	config = init_config();
	config->a = a;
	config->b = b;
	parse_and_stack(ac, av, a, config);
	select_algorithm(config, a);
	free_stack(a);
	free_stack(b);
	free(config);
	return (0);
}
