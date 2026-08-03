/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_medium_sort_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 22:00:00 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 10:16:24 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_sqrt(int nb)
{
	int	i;

	i = 1;
	if (nb <= 0)
		return (0);
	while (i * i <= nb)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (i - 1);
}

static void	bubble_sort_array(int *arr, int size)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

int	*get_sorted_array(t_stack *a)
{
	int		*reference_array;
	int		i;
	t_node	*curr;

	reference_array = malloc(sizeof(int) * a->size);
	if (!reference_array)
		return (NULL);
	curr = a->head;
	i = 0;
	while (curr)
	{
		reference_array[i++] = curr->number;
		curr = curr->next;
	}
	bubble_sort_array(reference_array, a->size);
	return (reference_array);
}

int	get_max_index_in_b(t_stack *stack)
{
	t_node	*curr;
	int		max_val;
	int		max_idx;
	int		curr_idx;

	if (!stack || !stack->head)
		return (-1);
	curr = stack->head;
	max_val = curr->number;
	max_idx = 0;
	curr_idx = 0;
	while (curr)
	{
		if (curr->number > max_val)
		{
			max_val = curr->number;
			max_idx = curr_idx;
		}
		curr = curr->next;
		curr_idx++;
	}
	return (max_idx);
}
