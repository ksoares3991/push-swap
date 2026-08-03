/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_complex_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:58:44 by kasoares          #+#    #+#             */
/*   Updated: 2026/08/03 16:16:45 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	partition_chunk(t_state *state, int pivot, int size)
{
	int	stays_count;

	stays_count = 0;
	while (size > 0)
	{
		if (state->a->head->index <= pivot)
			pb(state);
		else
		{
			ra(state);
			stays_count++;
		}
		size--;
	}
	return (stays_count);
}

static void	restore_stays(t_state *state, int stays_count)
{
	while (stays_count > 0)
	{
		rra(state);
		stays_count--;
	}
}

static void	restore_goes(t_state *state, int goes_count)
{
	while (goes_count > 0)
	{
		pa(state);
		goes_count--;
	}
}

void	order_chunk(t_state *state, int low, int high)
{
	int	size;
	int	pivot;
	int	stays_count;
	int	goes_count;
	int	rest_empty;

	size = high - low + 1;
	if (size <= 1)
		return ;
	if (size == 2)
	{
		if (state->a->head->index > state->a->head->next->index)
			sa(state);
		return ;
	}
	pivot = (low + high) / 2;
	rest_empty = (state->a->size == size);
	stays_count = partition_chunk(state, pivot, size);
	goes_count = size - stays_count;
	if (!rest_empty)
		restore_stays(state, stays_count);
	order_chunk (state, pivot + 1, high);
	restore_goes (state, goes_count);
	order_chunk (state, low, pivot);
}

void	quick_sort(t_state *state)
{
	normalize_ranks(state);
	order_chunk(state, 0, state->total_elements - 1);
}
