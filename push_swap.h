#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_node
{
	int				number;
	struct s_node	*next;
	struct s_node	*prev;
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
	PRINT_ON,
}	t_print;

typedef struct s_bench
{
	int	count_op[TOTAL];
}	t_bench;

typedef struct s_state
{
	t_stack	*a;
	t_stack	*b;
	t_bench	*bench;
	int		total_elements;
	t_print	print_mode;
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
void	selection_sort(t_state *state);
long	ft_atol(char *s);
int ft_strcmp(const char *s1, char *s2);
int ft_isnumber(char *s);

#endif
