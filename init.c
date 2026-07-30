/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:19:35 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/30 18:23:11 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	config = malloc(sizeof(t_state));
	if (!config)
		return (NULL);
	config->strategy = 0;
	config->bench_mode = 0;
	config->total_flags = 0;
	config->a = NULL;
	config->b = NULL;
	config->bench = NULL;
	config->print_mode = PRINT_ON;
	config->total_elements = 0;
	return (config);
}
