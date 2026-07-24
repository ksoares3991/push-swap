/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:17:58 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/24 13:26:33 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	do_push(t_stack *stack_src, t_stack *stack_dst)
{
	t_node	*src;
	t_node	*dst;

	if (!stack_src)
		return ;
	src = stack_src->head;
	if (stack_dst->size <= 0)
	{
		stack_dst->head = src;
		stack_dst->tail = src;
		stack_dst->head->prev = NULL;
		stack_dst->head->next = NULL;
	}
	else
	{
		src->next = stack_dst->head;
		stack_dst->head->prev = src;
		stack_dst->head = src;
		stack_dst->tail->prev = stack_dst->head->next; //check redundance
	}
}
void	pa(t_stack *stack_a, t_stack *stack_b)
{
	do_push(stack_a, stack_b);
	write(1, "pa\n", 3);
	count_op[PA]++;
	count_op[TOTAL]++;
}
void	pb(t_stack *stack_b, t_stack *stack_a)
{
	do_swap(stack_b, stack_a);
	write(1, "pb\n", 3);
	count_op[PB]++;
	count_op[TOTAL]++;
}
