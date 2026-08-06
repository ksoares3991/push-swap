
#include "push_swap.h"

float	get_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	float	mistakes;
	float	total_pairs;

	if (a->size <= 1)
		return (0.0);
	total_pairs = (float)((long)(a->size * (a->size - 1) / 2));
	mistakes = 0;
	i = a->head;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (i->number > j->number)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	return (mistakes / total_pairs);
}

static	void	adaptive_select(t_state *config, t_stack *a, float disorder)
{
	if (a->size <= 1 || is_sorted(a))
		return ;
	if (a->size == 2)
		return (order_two(config));
	if (a->size == 3)
		return (order_three(config));
	if (a->size <= 5)
		return (selection_sort(config));
	if ((disorder < 0.2) || config->strategy == STRAT_SIMPLE)
		selection_sort(config);
	else if ((disorder >= 0.2 && disorder < 0.5)
		|| config->strategy == STRAT_MEDIUM)
		medium_sort(config);
	else if ((disorder >= 0.5) || config->strategy == STRAT_COMPLEX)
		quick_sort(config);
}

void	select_algorithm(t_state *config, t_stack *a)
{
	float	initial_disorder;

	initial_disorder = 0.0;
	if (!config->strategy || config->strategy == STRAT_ADAPTIVE
		|| config->bench_mode)
		initial_disorder = get_disorder(a);
	if (!config->strategy || config->strategy == STRAT_ADAPTIVE)
		adaptive_select(config, a, initial_disorder);
	else if (config->strategy == STRAT_SIMPLE)
		selection_sort(config);
	else if (config->strategy == STRAT_MEDIUM)
		medium_sort(config);
	else if (config->strategy == STRAT_COMPLEX)
		quick_sort(config);
	if (config->total_elements < 1)
		print_error(a, config, NULL);
	if (config->bench_mode)
		print_bench(config, initial_disorder);
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_state	*config;

	if (ac < 2)
		return (0);
	a = init_stack();
	b = init_stack();
	config = init_config();
	if (!a || !b || !config)
		return (1);
	config->a = a;
	config->b = b;
	parse_and_stack(ac, av, a, config);
	select_algorithm(config, a);
	free_stack(a);
	free_stack(b);
	free(config->bench);
	free(config);
	return (0);
}
