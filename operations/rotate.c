/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 17:18:06 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/29 18:49:55 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	do_rotate(t_stack *stack)
{
	t_node	*first;
	t_node	*last;

	// Garante que a pilha e o tail existem e têm pelo menos 2 elementos
	if (!stack || !stack->head || !stack->head->next || !stack->tail || stack->size < 2)
		return ;
	first = stack->head;
	last = stack->tail;
	stack->head = first->next;
	stack->head->prev = NULL;
	last->next = first;
	first->prev = last;
	first->next = NULL;
	stack->tail = first;
}

void	ra(t_state *state)
{
	if (!state || !state->a)
		return ;
	do_rotate(state->a);
	if (state->print_mode == PRINT_ON)
		write(1, "ra\n", 3);
	// Proteção contra bench == NULL
	if (state->bench)
	{
		state->bench->count_op[RA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rb(t_state *state)
{
	if (!state || !state->b)
		return ;
	do_rotate(state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "rb\n", 3);
	// Proteção contra bench == NULL
	if (state->bench)
	{
		state->bench->count_op[RB]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	rr(t_state *state)
{
	if (!state || !state->a || !state->b)
		return ;
	do_rotate(state->a);
	do_rotate(state->b);
	if (state->print_mode == PRINT_ON)
		write(1, "rr\n", 3);
	// Proteção contra bench == NULL
	if (state->bench)
	{
		state->bench->count_op[RR]++;
		state->bench->count_op[TOTAL]++;
	}
}