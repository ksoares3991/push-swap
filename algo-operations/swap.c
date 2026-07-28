/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:58:30 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/27 18:42:09 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

static void	do_swap(t_stack *stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || stack->size < 2)
		return ;
	first = stack->head;
	second = stack->head->next;
	first->next = second->next;
	second->next = first;
	stack->head = second;
}

void	sa(t_stack *a, t_state *state)
{
	do_swap(a);
	if (state->print_mode == PRINT_ON)
		write(1, "sa\n", 3);
	state->bench->count_op[SA]++;
	state->bench->count_op[TOTAL]++;
}

void	sb(t_stack *b, t_state *state)
{
	do_swap(b);
	if (state->print_mode == PRINT_ON)
		write(1, "sb\n", 3);
	state->bench->count_op[SB]++;
	state->bench->count_op[TOTAL]++;
}

void	ss(t_stack *a, t_stack *b, t_state *state)
{
	do_swap(a);
	do_swap(b);
	if (state->print_mode == PRINT_ON)
		write(1, "ss\n", 3);
	state->bench->count_op[SS]++;
	state->bench->count_op[TOTAL]++;
}
