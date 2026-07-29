/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 14:26:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/29 17:25:23 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_node_index(t_stack *stack, t_node *node)
{
	t_node	*current;
	int		i;

	i = 0;
	current = stack->head;
	while (current != NULL && current != node)
	{
		i++;
		current = current->next;
	}
	return (i);
}

t_node	*find_smallest(t_stack *stack)
{
	t_node	*smallest;
	t_node	*current;

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

void	order_two(t_state *state)
{
	int	first;
	int	second;

	if (!state->a || state->a->size != 2)
		return ;
	first = state->a->head->number;
	second = state->a->head->next->number;
	if (first > second)
		sa(state);
}

void	order_three(t_state *state)
{
	int	first;
	int	second;
	int	third;

	if (!state->a || state->a->size != 3)
		return ;
	first = state->a->head->number;
	second = state->a->head->next->number;
	third = state->a->tail->number;
	if (first > second && first < third)
		sa(state);
	else if (first > second && second > third)
	{
		sa(state);
		rra(state);
	}
	else if (first > second && first > third && second < third)
		ra(state);
	else if (first < second && first < third && second > third)
	{
		sa(state);
		ra(state);
	}
	else if (first < second && first > third)
		rra(state);
}

void	selection_sort(t_state *state, int position, t_node *smallest)
{
	if (state->a->size == 2)
		order_two(state);
	else if (state->a->size == 3)
		order_three(state);
	else if (state->a->size > 3)
	{
		while (state->a->size > 3)
		{
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
		order_three(state);
		while (state->b->size > 0)
			pa(state);
	}
}
