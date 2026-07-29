/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:58:30 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/29 16:52:16 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void do_swap(t_stack *stack)
{
	t_node *first;
	t_node *second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack->tail = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	stack->head = second;
}

void	sa(t_state *state)
{
	do_swap(state->a);
	if (state->print_mode == PRINT_ON)
		write(1, "sa\n", 3);
	state->bench->count_op[SA]++;
	state->bench->count_op[TOTAL]++;
}

void	sb(t_state *state)
{
	do_swap(state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "sb\n", 3);
	state->bench->count_op[SB]++;
	state->bench->count_op[TOTAL]++;
}

void	ss(t_state *state)
{
	do_swap(state->a);
	do_swap(state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "ss\n", 3);
	state->bench->count_op[SS]++;
	state->bench->count_op[TOTAL]++;
}
