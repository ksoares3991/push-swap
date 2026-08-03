/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 23:45:00 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/03 19:00:25 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

char	**get_flags(void)
{
	static char	*flags[6] = {
		"",
		"--simple",
		"--medium",
		"--complex",
		"--adaptive",
		"--bench"
	};

	return ((char **)flags);
}

int	search_flag(char *av)
{
	int	i;

	i = 0;
	if (!av)
		return (0);
	while (i < 6)
	{
		if (ft_strcmp((get_flags()[i]), av))
			return (i);
		i++;
	}
	return (0);
}
