/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/27 18:46:11 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	do_rotate(t_stack *stack)
{
	t_node	*old_head;

	if (!stack || stack->size < 2)
		return ;
	old_head = stack->head;
	stack->head = old_head->next;
	stack->head->prev = NULL;
	old_head->prev = stack->tail;
	old_head->next = NULL;
	stack->tail = old_head;
}

void	ra(t_stack *a, t_state *state)
{
	do_rotate(a);
	if (state->print_mode == PRINT_ON)
		write(1, "ra\n", 3);
	state->bench->count_op[RA]++;
	state->bench->count_op[TOTAL]++;
}

void	rb(t_stack *b, t_state *state)
{
	do_rotate(b);
	if (state->print_mode == PRINT_ON)
		write(1, "rb\n", 3);
	state->bench->count_op[RB]++;
	state->bench->count_op[TOTAL]++;
}

void	rr(t_stack *a, t_stack *b, t_state *state)
{
	do_rotate(a);
	do_rotate(b);
	if (state->print_mode == PRINT_ON)
		write(1, "rr\n", 3);
	state->bench->count_op[RR]++;
	state->bench->count_op[TOTAL]++;
}
