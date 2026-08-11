
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

int	get_max_index_in_b(t_stack *stack)
{
	t_node	*curr;
	int		max_index;
	int		max_pos;
	int		curr_pos;

	if (!stack || !stack->head)
		return (-1);
	curr = stack->head;
	max_index = curr->index;
	max_pos = 0;
	curr_pos = 0;
	while (curr)
	{
		if (curr->index > max_index)
		{
			max_index = curr->index;
			max_pos = curr_pos;
		}
		curr = curr->next;
		curr_pos++;
	}
	return (max_pos);
}
