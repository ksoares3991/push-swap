/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 15:58:30 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/23 19:08:09 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
void	sa(t_stack *stack_a)
{
	do_swap(stack_a);
	write(1, "sa\n", 3);
	count_op[SA]++;
	count_op[TOTAL]++;
}
void	sb(t_stack *stack_b)
{
	do_swap(stack_b);
	write(1, "sb\n", 3);
	count_op[SB]++;
	count_op[TOTAL]++;
}
void	ss(t_stack *stack_a, t_stack *stack_b)
{
	do_swap(stack_a);
	do_swap(stack_b);
	write(1, "ss\n", 3);
	count_op[SS]++;
	count_op[TOTAL]++;
}
