/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 00:16:36 by kasoares         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include "ft_printf.h"
# include "libft.h"

typedef struct s_node
{
	struct s_node	*next;
	struct s_node	*prev;
	int				number;
	int				index; // Must be initialize to allow quicksort to work properly
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

typedef enum e_print
{
	PRINT_OFF,
	PRINT_ON
}	t_print;

typedef struct s_bench
{
	int	count_op[(TOTAL + 1)];
}	t_bench;

typedef struct s_state
{
	int		strategy;
	int		bench_mode;
	int		total_flags;
	int		total_elements;
	t_stack	*a;
	t_stack	*b;
	t_bench	*bench;
	t_print	print_mode;
}	t_state;
//Elementary operations
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
//Global auxiliary sorting functions
int		is_sorted(t_stack *stack);
void	order_two(t_state *state);
void	order_three(t_state *state);
//Selection sort functions
void	selection_sort(t_state *state);
//Quick sort functions
void	normalize_ranks(t_state *state);
void	order_chunk(t_state *state, int low, int high);
void	quick_sort(t_state *state);

char	**get_flags(void);
int		search_flag(char *av);
float	get_disorder(t_stack *a);
void	adaptive_select(t_state *config, t_stack *a);
void	select_algorithm(t_state *config, t_stack *a);

void	print_error(t_stack *a, t_state *config, char **f_str);
void	print_bench(t_state *config, float disorder);
int		is_int(long n, t_stack *a, t_state *config, char **f_str);
int		is_int(long n);
int		ft_isnumber(char *s, t_stack *a, t_state *config, char **f_str);
int		ft_isdigit(int c);
long	ft_atol(char *s);
int		ft_strcmp(const char *s1, char *s2);

int		is_dup(t_stack *a, int n, t_state *config, char **f_str);
void	add_to_stack(char *p_str, t_stack *a, t_state *config, char **f_str);
int		add_and_search(char *str, t_stack *a, t_state *config, char **f_str);
int		parse_and_stack(int ac, char **av, t_stack *a, t_state *config);

void	free_parsed_str(char **f_str);
void	free_stack(t_stack *stack);

t_stack	*init_stack(void);
t_state	*init_config(void);

void 	print_error_debug(t_state *state); // apagar essa joça antes de submeter projeto
#endif
