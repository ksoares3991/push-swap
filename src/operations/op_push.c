
#include "push_swap.h"

static int	do_push(t_stack *src, t_stack *dst)
{
	t_node	*node_to_move;

	if (!src || src->size == 0)
		return (0);
	node_to_move = src->head;
	src->head = src->head->next;
	if (src->head)
		src->head->prev = NULL;
	else
		src->tail = NULL;
	src->size--;
	node_to_move->next = dst->head;
	node_to_move->prev = NULL;
	if (dst->head)
		dst->head->prev = node_to_move;
	else
		dst->tail = node_to_move;
	dst->head = node_to_move;
	dst->size++;
	return (1);
}

void	pa(t_state *state)
{
	int	return_op;

	if (!state || !state->a || !state->b || state->b->size == 0)
		return ;
	return_op = do_push(state->b, state->a);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "pa\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[PA]++;
		state->bench->count_op[TOTAL]++;
	}
}

void	pb(t_state *state)
{
	int	return_op;

	if (!state || !state->a || !state->b || state->a->size == 0)
		return ;
	return_op = do_push(state->a, state->b);
	if (return_op == 1 && state->print_mode == PRINT_ON)
		write(1, "pb\n", 3);
	if (return_op == 1 && state->bench)
	{
		state->bench->count_op[PB]++;
		state->bench->count_op[TOTAL]++;
	}
}
