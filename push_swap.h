/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/20 15:56:33 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/07/23 14:13:39 by vicdos-s         ###   ########.fr       */
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