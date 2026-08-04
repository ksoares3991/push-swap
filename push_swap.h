/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/04 17:39:38 by vicdos-s         ###   ########.fr       */
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
	int				index;
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
	t_stack	*a;
	t_stack	*b;
	t_bench	*bench;
	t_print	print_mode;
	int		total_elements;
}	t_state;

t_stack	*init_stack(void);
t_state	*init_config(void);

int		parse_and_stack(int ac, char **av, t_stack *a, t_state *config);
int		add_and_search(char *str, t_stack *a, t_state *config, char **f_str);
void	add_to_stack(char *p_str, t_stack *a, t_state *config, char **f_str);
int		is_dup(t_stack *a, int n, t_state *config, char **f_str);
char	**get_flags(void);
int		search_flag(char *av);

int		is_int(long n, t_stack *a, t_state *config, char **f_str);
int		ft_isnumber(char *s, t_stack *a, t_state *config, char **f_str);
long	ft_atol(char *s);
int		match_str(const char *s1, char *s2);
int		ft_sqrt(int nb);

void	select_algorithm(t_state *config, t_stack *a);
void	order_two(t_state *state);
void	order_three(t_state *state);
void	medium_sort(t_state *state);
void	selection_sort(t_state *state);
void	quick_sort(t_state *state);

int		is_sorted(t_stack *stack);
int		*get_sorted_array(t_stack *a);
int		get_max_index_in_b(t_stack *stack);
void	normalize_ranks(t_state *state);
float	get_disorder(t_stack *a);

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

void	print_error(t_stack *a, t_state *config, char **f_str);
void	print_bench(t_state *config, float disorder);

void	free_parsed_str(char **f_str);
void	free_stack(t_stack *stack);

#endif