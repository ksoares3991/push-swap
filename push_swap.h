/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasoares <kasoares@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/27 16:41:51 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h> //TO BE REMOVED
# include "ft_printf.h"
# include "libft.h"

long	ft_atol(char *s);
int		ft_isdigit(int c);
int		ft_isnumber(char *s);
int		ft_strcmp(const char *s1, char *s2);

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				number;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;

typedef enum e_op
{
	SA,
	SB,
	SS,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	PA,
	PB,
	TOTAL
}	t_op;

typedef enum e_print // select to print or to not print bench
{
	PRINT_OFF,
	PRINT_ON
}	t_print;

typedef struct s_bench //observe and register performance metrics
{
	int	count_op[TOTAL];
}	t_bench;

typedef struct s_state // master: define game/environment current state
{
	t_stack	*a;
	t_stack	*b;
	t_bench	*bench;
	t_print	print_mode;
	int		total_elements; // static variable - single source of truth
}	t_state;

#endif
