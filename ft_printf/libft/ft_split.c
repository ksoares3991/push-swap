/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicdos-s <vicdos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 10:23:57 by vicdos-s          #+#    #+#             */
/*   Updated: 2026/06/10 11:52:25 by vicdos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strttl(const char *s, char c)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (s[i])
	{
		if ((s[i] != c) && (i == 0 || s[i - 1] == c))
			total++;
		i++;
	}
	return (total);
}

static	char	**ft_freestr(char **res, size_t j)
{
	while (j > 0)
	{
		j--;
		free(res[j]);
	}
	free(res);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	i;
	size_t	j;
	size_t	start;

	res = malloc((ft_strttl(s, c) + 1) * sizeof (char *));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		start = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		res[j++] = ft_substr(s, start, (i - start));
		if (!res[j - 1])
			return (ft_freestr(res, j));
	}
	res[j] = NULL;
	return (res);
}
