
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
