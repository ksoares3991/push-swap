/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:58:30 by kasoares          #+#    #+#             */
/*   Updated: 2026/08/01 18:22:21 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	do_rev_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || stack->size < 2)
		return (0);
	first = stack->head;
	last = stack->tail;
	stack->tail = last->prev;
	stack->tail->next = NULL;
	last->next = first;
	last->prev = NULL;
	first->prev = last;
	stack->head = last;
	return (1);
}

void	rra(t_state *state)
{
	int	return_op;

	if (!state || !state->a)
		return ;
	return_op = do_rev_rotate(state->a);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "rra\n", 4);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[RRA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rrb(t_state *state)
{
	int	return_op;

	if (!state || !state->b)
		return ;
	return_op = do_rev_rotate(state->b);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "rrb\n", 4);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[RRB]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rrr(t_state *state)
{
	int	return_op1;
	int	return_op2;

	if (!state || !state->a || !state->b)
		return ;
	return_op1 = do_rev_rotate(state->a);
	return_op2 = do_rev_rotate(state->b);
	if ((return_op1 == 1 || return_op2 == 1) && state->print_mode == PRINT_ON)
		write(1, "rrr\n", 4);
	if ((return_op1 == 1 || return_op2 == 1) && state->bench)
	{
		state->bench->count_op[RRR]++;
		state->bench->count_op[TOTAL]++;
	}
}
