/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:17:58 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/29 16:53:01 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void do_push(t_stack *src, t_stack *dst)
{
	t_node *node_to_move;

	if (!src || src->size == 0)
		return ;
	node_to_move = src->head;
	src->head = src->head->next;
	if (src->head)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	src->size--;
	node_to_move->next = dst->head;
	node_to_move->prev = NULL;
	if (dst->head)
		dst->head->prev = node_to_move;
	else
		dst->tail = node_to_move;
	dst->head = node_to_move;
	dst->size++;
}

void pa(t_state *state)
{
	if (!state->b || state->b->size == 0)
		return ;
	do_push(state->b, state->a);
	if (state->print == TRUE)
		write(1, "pa\n", 3);
	state->bench->count_op[PA]++;
	state->bench->count_op[TOTAL]++;
}

void pb(t_state *state)
{
	if (!state->a || state->a->size == 0)
		return ;
	do_push(state->a, state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "pb\n", 3);
	state->bench->count_op[PB]++;
	state->bench->count_op[TOTAL]++;
}
