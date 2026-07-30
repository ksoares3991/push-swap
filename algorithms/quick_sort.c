/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:58:44 by kasoares          #+#    #+#             */
/*   Updated: 2026/07/30 20:01:17 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*sort_temp_array(int *arr, int size)
{
	int	temp;
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[i])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}

int	get_pivot(t_state *state)
{
	t_node	*current_node;
	int		*lst_copy;
	int		lst_size;
	int		pivot;
	int		i;

	current_node = state->a->head;
	lst_size = state->a->size;
	lst_copy = malloc(sizeof(int) * lst_size);
	if (!lst_copy)
		return (0); // or print_error(state); // or exit_error - check naming convention with victor
	i = 0;
	while (current_node != NULL)
	{
		lst_copy[i] = current_node->number;
		current_node = current_node->next;
		i++;
	}
	pivot = sort_temp_array(lst_copy, lst_size)[lst_size / 2];
	free(lst_copy);
	return (pivot);
}

void	quick_sort(t_state *state)
{
	int	items_checked;
	int	chunk_size;
	int	rotated;
	int	pushed;
	int	pivot;

	if (chunk_size <= 3)
		order_three(state);
	else
	{
		pivot = get_pivot(state, chunk_size);
		pushed = 0;
		rotated = 0;
		items_checked = 0;
		if (items_checked < chunk_size)
		{

		}
		if (partition ended?)
		{

		}
		else
			rra(state) *rotated;
	}
}


