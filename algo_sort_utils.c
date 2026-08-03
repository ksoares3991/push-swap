/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 20:06:12 by kasoares          #+#    #+#             */
/*   Updated: 2026/08/01 20:20:30 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack)
		return (0);
	current = stack->head;
	while (current != NULL)
	{
		if (current == stack->tail)
			break ;
		else if (current->number > current->next->number)
			return (0);
		current = current->next;
	}
	return (1);
}

void	order_two(t_state *state)
{
	int	first;
	int	second;

	if (!state || !state->a || state->a->size != 2)
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

	if (!state || !state->a || state->a->size != 3)
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
