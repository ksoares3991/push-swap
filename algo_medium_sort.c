/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_medium_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 22:11:53 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 20:00:27 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void k_sort_phase1(t_state *state)
{
    int chunk_size;
    int pushed_count;
    int target_index;

    chunk_size = ft_sqrt(state->a->size) * 1.4;
    pushed_count = 0;
    while (state->a->size > 0)
    {
        target_index = state->a->head->index;
        
        if (target_index <= pushed_count)
        {
            pb(state);
            rb(state);
            pushed_count++;
        }
        else if (target_index <= pushed_count + chunk_size)
        {
            pb(state);
            pushed_count++;
        }
        else
            ra(state);
    }
}

static void k_sort_phase2(t_state *state)
{
    int highest_val_pos;

    while (state->b->size > 0)
    {
        highest_val_pos = get_max_index_in_b(state->b);
        if (highest_val_pos <= state->b->size / 2)
        {
            while (highest_val_pos > 0)
            {
                rb(state);
                highest_val_pos--;
            }
        }
        else
        {
            highest_val_pos = state->b->size - highest_val_pos;
            while (highest_val_pos > 0)
            {
                rrb(state);
                highest_val_pos--;
            }
        }
        pa(state);
    }
}

void    medium_sort(t_state *state)
{
    if (!state || !state->a || state->a->size <= 1)
        return ;
    normalize_ranks(state);
    if (is_sorted(state->a) == 1)
        return ;
    if (state->a->size == 2)
        order_two(state);
    else if (state->a->size == 3)
        order_three(state);
    else if (state->a->size > 3)
    {
        k_sort_phase1(state);
        k_sort_phase2(state);
    }
}