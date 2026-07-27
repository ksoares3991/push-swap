/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:17:58 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/27 18:42:30 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	do_push(t_stack *stack_src, t_stack *stack_dst)
{
	t_node	*src;
	t_node	*dst;

	if (!stack_src)
		return ;
	src = stack_src->head;
	stack_src->head = src->next;
	if (stack_src->head != NULL)
		stack_src->head->prev = NULL;
	else
		stack_src->tail = NULL;
	stack_src->size--;
	src->next = stack_dst->head;
	src->prev = NULL;
	if (stack_dst->size == 0)
		stack_dst->tail = src;
		stack_dst->head->prev = src;
	stack_dst->head = src;
	stack_dst->size++;
}

void	pa(t_stack *a, t_stack *b, t_state *state)
{
	if (!b || b->size == 0)
		return ;
	do_push(b, a);
	if (state->print_mode == PRINT_ON)
		write(1, "pa\n", 3);
	state->bench->count_op[PA]++;
	state->bench->count_op[TOTAL]++;
}

void	pb(t_stack *a, t_stack *b, t_state *state)
{
	if (!a || a ->size == 0)
		return ;
	do_push(a, b);
	if (state->print_mode == PRINT_ON)
		write(1, "pb\n", 3);
	state->bench->count_op[PB]++;
	state->bench->count_op[TOTAL]++;
}
