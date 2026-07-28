/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/28 13:33:18 by vicdos-s         ###   ########.fr       */
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
int	parser(int ac, char **av, t_stack *a)
{
	char **parsed_str;
	int i;
	int k;
	t_node *new_node;
	
	i = 1;	
	while (i < ac)
	{
		(void)a;
		k = 0;
		parsed_str = ft_split(av[i], ' ');
		while (parsed_str && parsed_str[k])
		{
			if (ft_isnumber(parsed_str[k]))
			{
				new_node = malloc(sizeof(t_node));
				new_node->prev = a->tail;
				new_node->next = NULL;
				new_node->number = ft_atol(parsed_str[k]);
				if (!a->head)
				{
					a->head = new_node;
					a->tail = new_node;
					k++;
				}
				else
				{
					a->tail = new_node;
					k++;
				}
				ft_printf("nó adicionado: %d\n", new_node->number);
			}
			if (!ft_isnumber(parsed_str[k]))
			{
				ft_putstr_fd("Error", 2);
				return (0);
			}
		}
		i++;
	}
	ft_printf("%s", parsed_str[0]);
	return (0);
}
void init_stack (t_stack *a)
{
	a->size = 0;
	a->tail = NULL;
	a->head = NULL;
}

int	main(int ac, char **av)
{
	t_stack *a;

	a = malloc(sizeof(t_stack));
	init_stack(a);

	parser(ac, av, a);
	
	while()
	
	
}

