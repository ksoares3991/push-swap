/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:02 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/30 14:48:32 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rev_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || stack->size < 2)
		return ;
	first = stack->head;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->next = first;
	last->prev = NULL;
	first->prev = last;
	stack->head = last;
}

void	rra(t_state *state)
{
	do_rev_rotate(state->a);
	if (state->print_mode == PRINT_ON)
		write(1, "rra\n", 4);
	if (state->bench)
	{
		state->bench->count_op[RRA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rrb(t_state *state)
{
	do_rev_rotate(state->b);if (state->bench)
	if (state->print_mode == PRINT_ON)
		write(1, "rrb\n", 4);
	if (state->bench)
	{
		state->bench->count_op[RRB]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rrr(t_state *state)
{
	do_rev_rotate(state->a);
	do_rev_rotate(state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "rrr\n", 4);
	if (state->bench)
	{
		state->bench->count_op[RRR]++;
		state->bench->count_op[TOTAL]++;
	}
}
