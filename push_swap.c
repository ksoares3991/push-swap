/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 16:36:17 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/23 14:40:53 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

	char	**get_flags(void)
{
	static char	*flags[5] = {
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
void	parser(int ac, char **av, t_stack *a)
{
	char **parsed_str;
	int i;
	int k;
	
	i = 1;	
	while (i < ac)
	{
		(void)a;
		k = 0;
		parsed_str = ft_split(av[i], ' ');
		while (parsed_str && parsed_str[k])
		{
			if (!ft_isnumber(parsed_str[k]) || (!search_flag(parsed_str[k])))
				{
					ft_putstr_fd("Error", 2);
					break ;
				}
			else
			k++;
		}
		i++;
	}
	ft_printf("%s", parsed_str[0]);
}
void init_stack (t_stack *a)
{
	a->size = 0;
	a->tail = NULL;
	a->head = NULL;
}

int	main(int ac, char **av)
{
	t_stack a;
	init_stack(&a);
	parser(ac, av, &a);
}

