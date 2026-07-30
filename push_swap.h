/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/30 13:18:08 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h> //TO BE REMOVED
# include "ft_printf.h"
# include "libft.h"



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
	int	count_op[(TOTAL + 1)];
}	t_bench;

typedef struct s_state // master: define game/environment current state
{
	int		strategy;
	int		bench_mode;
	int		total_flags;
	t_stack	*a;
	t_stack	*b;
	t_bench	*bench;
	t_print	print_mode;
	int		total_elements; // static variable - single source of truth
}	t_state;

void	sa(t_state *state);
void	sb(t_state *state);
void	ss(t_state *state);
void	ra(t_state *state);
void	rb(t_state *state);
void	rr(t_state *state);
void	rra(t_state *state);
void	rrb(t_state *state);
void	rrr(t_state *state);
void	pa(t_state *state);
void	pb(t_state *state);
void	selection_sort(t_state *state, int position, t_node *smallest);
long	ft_atol(char *s);
long	ft_atol(char *s);
int		ft_isdigit(int c);
int		ft_isnumber(char *s);
int		ft_strcmp(const char *s1, char *s2);
int 	is_int(long n);
void	print_error();
int 	search_flag(char *av);
void 	print_error_debug(t_state *state); // apagar essa joça antes de submeter projeto
#endif
