#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

extern char	**environ;

static char	error_identifier(char *str)
{
	if (!str)
		str = "\0";
	write(STDOUT_FILENO, "minishell: export: `", 20);
	write(STDOUT_FILENO, str, ft_strlen(str));
	write(STDOUT_FILENO, "': not a valid identifier\n", 26);
	set_exit_status_code(1);
	return (1);
}

static char	is_key_exist(size_t index, char *key, size_t key_len)
{
	char	*dup_key;

	dup_key = NULL;
	if (!ft_strncmp(environ[index], key, key_len))
	{
		dup_key = ft_strdup(key);
		if (dup_key)
		{
			free(environ[index]);
			environ[index] = dup_key;
		}
		return (1);
	}
	return (0);
}

static char	check_key_to_append(char **str, size_t *key_len)
{
	char	*alnum;
	char	*sign;

	if (!(*str) || !ft_isalpha(*(*str)))
		return (error_identifier(*str));
	alnum = (*str) + 1;
	while (*alnum && *alnum != '=')
	{
		if (!ft_isalnum(*alnum) && *alnum != '_')
			return (error_identifier(*str));
		alnum++;
	}
	set_exit_status_code(0);
	sign = ft_strchr(*str, '=');
	if (!sign)
		return (1);
	*sign = '\0';
	*key_len = ft_strlen(*str) + 1;
	*sign = '=';
	return (0);
}

/* void	environ_append(char *str);
 *
 *	Checking whether the key should be appended or
 *	if it already exists in the environ array.
 *	Finding space by shifting the existing environment
 *	variables until it reaches the "?=" variable.
 *	Inserting the new variable in the correct position.
 *	Handling memory allocation failures by reverting the
 *	insertion if ft_strdup fails.
 */
void	environ_append(char *str)
{
	size_t	key_len;
	size_t	index;

	if (check_key_to_append(&str, &key_len))
		return ;
	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		if (is_key_exist(index, str, key_len))
			return ;
		index++;
	}
	while (environ[index])
		index++;
	environ[index + 1] = NULL;
	index--;
	while (environ[index] && environ[index][0] != 63)
	{
		environ[index + 1] = environ[index];
		index--;
	}
	environ[index + 1] = environ[index];
	environ[index] = ft_strdup(str);
	if (!environ[index])
		environ[index] = environ[index + 1];
}
