
#include "push_swap.h"
#include <limits.h>

void	print_error(t_stack *a, t_state *config, char **f_str)
{
	if (a)
		free_stack(a);
	if (config)
	{
		if (config->bench)
			free(config->bench);
		if (config->b)
			free_stack(config->b);
		free(config);
	}
	if (f_str)
		free_parsed_str(f_str);
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

int	is_int(long n, t_stack *a, t_state *config, char **f_str)
{
	if (n > 2147483647 || n < -2147483648)
		print_error(a, config, f_str);
	return (1);
}

int	ft_isnumber(char *s, t_stack *a, t_state *config, char **f_str)
{
	long	i;

	i = 0;
	if (search_flag(s))
		return (0);
	if (!s || s[0] == '\0')
		print_error(a, config, f_str);
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		print_error(a, config, f_str);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			print_error(a, config, f_str);
		i++;
	}
	is_int(ft_atol(s), a, config, f_str);
	return (1);
}

long	ft_atol(char *s)
{
	long	i;
	long	result;
	int		is_negative;

	is_negative = 0;
	i = 0;
	result = 0;
	while (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			is_negative = 1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		if (result > (2147483647L - (s[i] - '0')) / 10)
			return (is_negative ? LONG_MIN : LONG_MAX);
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	if (is_negative)
		return (-result);
	return (result);
}

void	free_stack(t_stack *stack)
{
	t_node	*tmp;

	if (!stack)
		return ;
	while (stack->head)
	{
		tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
	}
	free(stack);
}
