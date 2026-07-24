/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/23 19:55:26 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_rotate(t_stack *stack)
{
	t_node	*old_head;

	if (!stack || stack->size < 2)
		return ;
	// saving old 1st node
	old_head = stack->head;
	// pointing the head to the 2nd node
	stack->head = old_head->next;
	// new 1st node prev point to NULL
	stack->head->prev = NULL;
	// old 1st node starts to link to the end of the list
	// new tail prev points to previous tail (still current before mod)
	old_head->prev = stack->tail;
	// new tail next points to NULL
	old_head->next = NULL;
	// old tail point to old head
	stack->tail = old_head;
}
void	ra(t_stack *stack_a)
{
	do_rotate(stack_a);
	write(1, "ra\n", 3);
	count_op[RA]++;
	count_op[TOTAL]++;
}
void	rb(t_stack *stack_b)
{
	do_rotate(stack_b);
	write(1, "rb\n", 3);
	count_op[RB]++;
	count_op[TOTAL]++;
}
void	rr(t_stack *stack_a, t_stack *stack_b)
{
	do_rotate(stack_a);
	do_rotate(stack_b);
	write(1, "rr\n", 3);
	count_op[RR]++;
	count_op[TOTAL]++;
}
