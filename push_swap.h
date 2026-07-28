/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/07/28 10:45:26 by vicdos-s         ###   ########.fr       */
=======
/*   Updated: 2026/07/27 16:41:51 by kasoares         ###   ########.fr       */
>>>>>>> 041a5511859465f2f4e8703772a2d8cdef6daf52
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

<<<<<<< HEAD
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
=======
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
>>>>>>> 041a5511859465f2f4e8703772a2d8cdef6daf52
