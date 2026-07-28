/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:26:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/27 18:48:14 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_node	*find_smallest(t_stack *stack)
{
	t_node	smallest;
	t_node	current;

	smallest = stack->head;
	current = stack->head;
	while (current != NULL)
	{
		if (current->value < smallest->value)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}

void	selection_sort(t_stack *a, t_stack *b, int list_size)
{
	t_node	smallest;
	int		position;

	while (a->size > 3)
	{
		smallest = find_smallest(a);
		position = smallest->index;
		while (a->head != smallest)
		{
			if (position <= (a->size / 2))
				ra(a);
			else
				rra(a);
		}
		pb(a, b);
	}
}
