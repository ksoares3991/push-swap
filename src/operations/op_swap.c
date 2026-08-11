
#include "push_swap.h"

static int	do_swap(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	if (!stack || stack->size < 2)
		return (0);
	first = stack->head;
	second = first->next;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
	else
		stack->tail = first;
	second->prev = NULL;
	second->next = first;
	first->prev = second;
	stack->head = second;
	return (1);
}

void	sa(t_state *state)
{
	int	return_op;

	if (!state || !state->a)
		return ;
	return_op = do_swap(state->a);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "sa\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[SA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	sb(t_state *state)
{
	int	return_op;

	if (!state || !state->b)
		return ;
	return_op = do_swap(state->b);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "sb\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[SB]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	ss(t_state *state)
{
	int	return_op1;
	int	return_op2;

	if (!state || !state->a || !state->b)
		return ;
	return_op1 = do_swap(state->a);
	return_op2 = do_swap(state->b);
	if ((return_op1 == 1 || return_op2 == 1) && state->print_mode == PRINT_ON)
		write(1, "ss\n", 3);
	if ((return_op1 == 1 || return_op2 == 1) && state->bench)
	{
		state->bench->count_op[SS]++;
		state->bench->count_op[TOTAL]++;
	}
}
