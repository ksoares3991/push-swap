/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/30 18:19:49 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**get_flags(void)
{
	static char	*flags[6] = {
		"",
		"--simple",
		"--medium",
		"--complex",
		"--adaptive",
		"--bench"
	};

	return ((char **)flags);
}

int	search_flag(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (i < 6)
	{
		if (ft_strcmp((get_flags()[i]), av))
			return (i);
		i++;
	}
	return (0);
}

float	get_disorder(t_stack *a)
{
	t_node	*i;
	t_node	*j;
	float	mistakes;
	float	total_pairs;

	total_pairs = (a->size * (a->size - 1) / 2);
	mistakes = 0;
	i = a->head;
	if (a->size <= 1)
		return (0.0);
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

void	adaptive_select(t_state *config, t_stack *a)
{
	int	final_disorder;

	final_disorder = (get_disorder(a) * 10000);
	if (config->bench_mode)
		ft_printf("[bench] disorder: %d,%d%%\n", (final_disorder / 100),
			(final_disorder % 100));
	if ((!config->strategy && get_disorder(a) < 0.2)
		|| config->strategy == 1)
		selection_sort(config, 0, NULL);
	if ((!config->strategy && get_disorder(a) >= 0.2
			&& get_disorder(a) < 0.5) || config->strategy == 2)
		printf("MEDIUM PLACEHOLDER");
	if ((!config->strategy && get_disorder(a) >= 0.5
			&& get_disorder(a) < 1) || config->strategy == 3)
		printf("COMPLEX PLACEHOLDER");
}

void	select_algorithm(t_state *config, t_stack *a)
{
	if (config->bench_mode)
		config->print_mode++;
	if (!config->strategy || config->strategy == 4)
		adaptive_select(config, a);
	else if (config->strategy == 1)
		selection_sort(config, 0, NULL);
	if (config->strategy == 2)
		printf("MEDIUM PLACEHOLDER");
	if (config->strategy == 3)
		printf("COMPLEX PLACEHOLDER");
}

int	main(int ac, char **av)
{
	t_stack	*a;
	t_stack	*b;
	t_state	*config;

	a = init_stack();
	b = init_stack();
	config = init_config();
	config->a = a;
	config->b = b;
	parse_and_stack(ac, av, a, config);
	select_algorithm(config, a);
	free(a);
	return (0);
}
