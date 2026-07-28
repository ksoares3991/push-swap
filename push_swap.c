/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/28 15:17:25 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

	char	**get_flags(void)
{
	static char	*flags[6] = {
		"\0",
		"--simple",
		"--medium",
		"--complex",
		"--adaptive",
		"--bench"
	};

	return (&*flags);
}
char *search_flag(char *av)
{
	int	i;
	
	i = 0;
	if (!av)
		return(("Error"));
	while (i < 5)
	{
		if (ft_strcmp((get_flags()[i]), av))
			return (get_flags()[i]);
		i++;
	}
	return ("Error");
}

void add_to_stack(char *p_str, t_stack *a)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->prev = a->tail;
	new_node->next = NULL;
	new_node->number = ft_atol(p_str);
	if (!a->head)
	{
		a->head = new_node;
		a->tail = new_node;
	}
	else
	{
		a->tail->next = new_node;
		a->tail = new_node;
	}
	a->size++;
	ft_printf("Size atual: %d\n", a->size);
}
int	parser(int ac, char **av, t_stack *a)
{
	char **parsed_str;
	int i;
	int k;

	i = 1;	
	while (i < ac)
	{			
		k = 0;
		parsed_str = ft_split(av[i], ' ');
		while (parsed_str && parsed_str[k])
		{
			if (ft_isnumber(parsed_str[k]))
				add_to_stack(parsed_str[k], a);
			k++;
		}
		i++;
	}
	return (1);
}

t_stack *init_stack (void)
{
	t_stack *stack;
	
	stack = malloc(sizeof(t_stack));
		if (!stack)
			return NULL;
	stack->size = 0;
	stack->tail = NULL;
	stack->head = NULL;
	return (stack);
}

int	main(int ac, char **av)
{
	t_stack *a;
	t_stack *b;
	t_node *act;
	
	a = init_stack();
	b = init_stack();

	parser(ac, av, a);
		act = a->head;
	while(act)
	{
		ft_printf("Nó atual: %d\n", act->number);
		act = act->next;
	}
	ft_printf("Size final: %d", a->size);
	free(act);
	free(a);
}

