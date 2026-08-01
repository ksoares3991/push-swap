/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:26:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/08/01 20:44:03 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_node_index(t_stack *stack, t_node *node)
{
	t_node	*current;
	int		i;

	if (!stack || !node)
		return (-1);
	i = 0;
	current = stack->head;
	while (current != NULL && current != node)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static t_node	*find_smallest(t_stack *stack)
{
	t_node	*smallest;
	t_node	*current;

	if (!stack || !stack->head)
		return (NULL);
	smallest = stack->head;
	current = stack->head;
	while (current != NULL)
	{
		if (current->number < smallest->number)
			smallest = current;
		current = current->next;
	}
	return (smallest);
}

static void	push_smallest_to_b(t_state *state)
{
	int		position;
	t_node	*smallest;

	smallest = find_smallest(state->a);
	position = get_node_index(state->a, smallest);
	while (state->a->head != smallest)
	{
		if (position <= (state->a->size / 2))
			ra(state);
		else
			rra(state);
	}
	pb(state);
}

void	selection_sort(t_state *state)
{
	if (is_sorted(state->a) == 1)
		return ;
	if (state->a->size == 2)
		order_two(state);
	else if (state->a->size == 3)
		order_three(state);
	else if (state->a->size > 3)
	{
		while (state->a->size > 3)
			push_smallest_to_b(state);
		order_three(state);
		while (state->b->size > 0)
			pa(state);
	}
}
