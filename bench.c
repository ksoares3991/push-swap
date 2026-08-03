/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/01 03:08:56 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/02 19:50:01 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_op_count(char *name, int count)
{
	ft_putstr_fd(name, 2);
	ft_putnbr_fd(count, 2);
}

static void	print_bench_ops(t_state *config, int total)
{
	print_op_count("[bench] total_ops: ", total);
	print_op_count("\n[bench] sa: ", config->bench->count_op[SA]);
	print_op_count(" sb: ", config->bench->count_op[SB]);
	print_op_count(" ss: ", config->bench->count_op[SS]);
	print_op_count(" pa: ", config->bench->count_op[PA]);
	print_op_count(" pb: ", config->bench->count_op[PB]);
	print_op_count("\n[bench] ra: ", config->bench->count_op[RA]);
	print_op_count(" rb: ", config->bench->count_op[RB]);
	print_op_count(" rr: ", config->bench->count_op[RR]);
	print_op_count(" rra: ", config->bench->count_op[RRA]);
	print_op_count(" rrb: ", config->bench->count_op[RRB]);
	print_op_count(" rrr: ", config->bench->count_op[RRR]);
	ft_putstr_fd("\n", 2);
}

static void	print_bench_strategy(int strategy, float disorder, t_state *config)
{
	ft_putstr_fd("[bench] strategy: ", 2);
	if (strategy == 1)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (strategy == 2)
		ft_putstr_fd("Medium / O(n\xe2\x88\x9an)\n", 2);
	else if (strategy == 3)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else
	{
		if (config->a->size <= 5)
			ft_putstr_fd("Adaptive / O(n^2)\n", 2);
		else if (disorder < 0.2)
			ft_putstr_fd("Adaptive / O(n^2)\n", 2);
		else if (disorder >= 0.2 && disorder < 0.5)
			ft_putstr_fd("Adaptive / O(n\xe2\x88\x9an)\n", 2);
		else
			ft_putstr_fd("Adaptive / O(n log n)\n", 2);
	}
}

void	print_bench(t_state *config, float disorder)
{
	int	d_int;
	int	total;
	int	i;

	if (!config || !config->bench)
		return ;
	d_int = (int)(disorder * 10000);
	ft_putstr_fd("[bench] disorder: ", 2);
	ft_putnbr_fd(d_int / 100, 2);
	ft_putstr_fd(".", 2);
	if ((d_int % 100) < 10)
		ft_putstr_fd("0", 2);
	ft_putnbr_fd(d_int % 100, 2);
	ft_putstr_fd("%\n", 2);
	print_bench_strategy(config->strategy, disorder, config);
	i = 0;
	total = 0;
	while (i < TOTAL)
		total += config->bench->count_op[i++];
	print_bench_ops(config, total);
}
