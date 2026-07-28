/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/28 13:42:49 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_atol (char *s);
int		ft_isdigit(int c);
int		ft_isnumber(char *s);
int		ft_strcmp(const char *s1, char *s2);

#include <stdlib.h>
#include <stdio.h>
#include "ft_printf.h"
#include "libft.h"

typedef struct s_node
{
	int		number;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
	int		size;
}	t_stack;

// typedef struct benchmark
// {
// 	t_opcount count_op[12];
// }	t_bench;

// typedef enum s_opcount
// {
// 	SA,
// 	SB,
// 	SS,
// 	RA,
// 	RB,
// 	RR,
// 	RRA,
// 	RRB,
// 	RRR,
// 	PA,
// 	PB,
// 	TOTAL

// } t_opcount;
