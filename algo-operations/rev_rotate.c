/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:02 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/23 20:33:47 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_rev_rotate(t_stack *stack)
{
	t_node	*old tail;

	if (!stack || stack->size < 2)
		return ;
	// saving the old tail
	old_tail = stack->tail;
	// changing the tail
	stack->tail = old_tail->prev;
	// changing new tail next to NULL
	stack->tail->next = NULL;
	// previous head prev points now to old_tail
	stack->head->prev = old_tail;
	// old tail now becomes the new head:
	// new head next points to previous stack head
	old_tail->next = stack->head;
	// new head (old tail) prev now points to NULL
	old_tail->prev = NULL;
	// old head point to old tail
	stack->head = old_tail;
}
void	rra(t_stack *stack_a)
{
	do_rev_rotate(stack_a);
	write(1, "ra\n", 3);
	count_op[RRA]++;
	count_op[TOTAL]++;
}
void	rrb(t_stack *stack_b)
{
	do_rev_rotate(stack_b);
	write(1, "rb\n", 3);
	count_op[RRB]++;
	count_op[TOTAL]++;
}
void	rrr(t_stack *stack_a, t_stack *stack_b)
{
	do_rev_rotate(stack_a);
	do_rev_rotate(stack_b);
	write(1, "rr\n", 3);
	count_op[RRR]++;
	count_op[TOTAL]++;
}
