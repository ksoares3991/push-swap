/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/08/01 19:32:40 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	do_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	if (!stack || !stack->head || !stack->head->next || !stack->tail
		|| stack->size < 2)
		return (0);
	first = stack->head;
	last = stack->tail;
	stack->head = first->next;
	stack->head->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	stack->tail = first;
	return (1);
}

void	ra(t_state *state)
{
	int	return_op;

	if (!state || !state->a)
		return ;
	return_op = do_rotate(state->a);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "ra\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[RA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rb(t_state *state)
{
	int	return_op;

	if (!state || !state->b)
		return ;
	return_op = do_rotate(state->b);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "rb\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[RB]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rr(t_state *state)
{
	int	return_op1;
	int	return_op2;

	if (!state || !state->a || !state->b)
		return ;
	return_op1 = do_rotate(state->a);
	return_op2 = do_rotate(state->b);
	if ((return_op1 == 1 || return_op2 == 1) && state->print_mode == PRINT_ON)
		write(1, "rr\n", 3);
	if ((return_op1 == 1 || return_op2 == 1) && state->bench)
	{
		state->bench->count_op[RR]++;
		state->bench->count_op[TOTAL]++;
	}
}
