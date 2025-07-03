#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

extern char	**environ;

static void	error_environ(void)
{
	environ_destroy();
	exit(error_malloc());
}

static unsigned char	error_atol(void)
{
	return (0);
}

static void	environ_shlvl_increment(size_t *index)
{
	char	*shlvl_char;
	char	*value;
	long	shlvl;

	value = environ[*index] + 6;
	shlvl = ft_atol(value, error_atol);
	if (shlvl == LONG_MAX || shlvl < 0)
		shlvl = 0;
	else
		shlvl++;
	if (shlvl >= 1000 && shlvl <= 1000000000)
	{
		write(STDERR_FILENO, "minishell: warning: shell level too high, ", 42);
		write(STDERR_FILENO, "resetting to 1\n", 15);
		shlvl = 1;
	}
	shlvl_char = ft_ltoa(shlvl);
	if (!shlvl_char)
		error_environ();
	value = malloc(7 + ft_strlen(shlvl_char));
	ft_strncpy(value, "SHLVL=", 6);
	ft_strcat(value, shlvl_char);
	environ[*index] = value;
	free(shlvl_char);
	(*index)++;
}

/* void	environ_set(void);
 *
 *	The function duplicates all the existing environment
 *	variables from the global environ array into new memory
 *	and adds to end a new environment variable "?=0". It
 *	then ensures the array is properly terminated by setting
 *	the next element to NULL.
 *	If any memory allocation fails during this process, the
 *	function will cause the program to exit with an error.
 */
void	environ_set(void)
{
	size_t	index;

	if (!environ)
		exit(EXIT_FAILURE);
	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		if (!ft_strncmp(environ[index], "SHLVL=", 6))
		{
			environ_shlvl_increment(&index);
			continue ;
		}
		environ[index] = ft_strdup(environ[index]);
		if (!environ[index])
			error_environ();
		index++;
	}
	environ[index] = ft_strdup("?=0");
	if (!environ[index])
		error_environ();
	environ[index + 1] = NULL;
}

/* void	environ_destroy(void);
 *
 *	The function frees all environment variables until it
 *	encounters the "?=0" variable.
 *	After freeing the "?=0" variable, it search environment
 *	variables until it finds "PWD=", at which point it stops
 *	freeing and exits.
 */
void	environ_destroy(void)
{
	size_t	index;

	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		free(environ[index]);
		index++;
	}
	free(environ[index]);
	index++;
	while (environ[index])
	{
		if (!ft_strncmp(environ[index], "PWD=", 4))
		{
			free(environ[index]);
			return ;
		}
		index++;
	}
}
