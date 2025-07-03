#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

extern char	**environ;

void	set_exit_status_code(t_uint8 status_code)
{
	char	*str_code;
	size_t	index;

	if (!environ)
		return ;
	index = 0;
	while (environ[index])
	{
		if (!ft_strncmp(environ[index], "?=", 2))
			break ;
		index++;
	}
	if (!environ[index])
		return ;
	str_code = ft_ltoa(status_code);
	if (!str_code)
	{
		error_malloc();
		return ;
	}
	free(environ[index]);
	environ[index] = ft_strjoin("?=", str_code);
	free(str_code);
}

static t_uint8	error_atol(void)
{
	write(STDOUT_FILENO, "minishell: cannot resolve exit status code\n", 43);
	return (244);
}

t_uint8	get_exit_status_code(void)
{
	size_t	index;
	char	*value;

	index = 0;
	while (environ[index])
	{
		if (!ft_strncmp(environ[index], "?=", 2))
			break ;
		index++;
	}
	if (!environ[index])
		return (error_atol());
	value = environ[index] + 2;
	return ((t_uint8)ft_atol(value, error_atol));
}
