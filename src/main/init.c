
#include "push_swap.h"

t_stack	*init_stack(void)
{
	t_stack	*stack;

	stack = malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->size = 0;
	stack->tail = NULL;
	stack->head = NULL;
	return (stack);
}

t_state	*init_config(void)
{
	t_state	*config;
	int		i;

	config = malloc(sizeof(t_state));
	if (!config)
		return (NULL);
	config->bench = malloc(sizeof(t_bench));
	if (!config->bench)
	{
		free(config);
		return (NULL);
	}
	i = 0;
	while (i <= TOTAL)
		config->bench->count_op[i++] = 0;
	config->strategy = 0;
	config->bench_mode = 0;
	config->total_flags = 0;
	config->a = NULL;
	config->b = NULL;
	config->print_mode = PRINT_ON;
	config->total_elements = 0;
	return (config);
}
