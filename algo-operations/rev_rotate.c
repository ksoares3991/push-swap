/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:02 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/27 18:47:11 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	do_rev_rotate(t_stack *stack)
{
	t_node	*old_tail;

	if (!stack || stack->size < 2)
		return ;
	old_tail = stack->tail;
	stack->tail = old_tail->prev;
	stack->tail->next = NULL;
	stack->head->prev = old_tail;
	old_tail->next = stack->head;
	old_tail->prev = NULL;
	stack->head = old_tail;
}

void	rra(t_stack *a, t_state *state)
{
	do_rev_rotate(a);
	if (state->print_mode == PRINT_ON)
		write(1, "ra\n", 3);
	state->bench->count_op[RRA]++;
	state->bench->count_op[TOTAL]++;
}

void	rrb(t_stack *b, t_state *state)
{
	do_rev_rotate(b);
	if (state->print_mode == PRINT_ON)
		write(1, "rb\n", 3);
	state->bench->count_op[RRB]++;
	state->bench->count_op[TOTAL]++;
}

void	rrr(t_stack *a, t_stack *b, t_state *state)
{
	do_rev_rotate(a);
	do_rev_rotate(b);
	if (state->print_mode == PRINT_ON)
		write(1, "rr\n", 3);
	state->bench->count_op[RRR]++;
	state->bench->count_op[TOTAL]++;
}
