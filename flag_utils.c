/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 23:45:00 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/08/04 17:39:38 by vicdos-s         ###   ########.fr       */
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
		if (match_str((get_flags()[i]), av))
			return (i);
		i++;
	}
	return (0);
}
