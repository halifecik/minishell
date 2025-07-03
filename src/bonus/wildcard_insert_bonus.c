#include "minishell.h"

#include <stdlib.h>

static char	insert_ps(char **dirs, char *prefix, char *suffix, size_t suf_len)
{
	const size_t	prefix_len = ft_strlen(prefix);
	size_t			dir_len;
	size_t			index;
	char			mode;

	mode = 0;
	index = -1;
	while (dirs[++index])
	{
		dir_len = ft_strlen(dirs[index]);
		if (prefix_len + suf_len <= dir_len
			&& !ft_strncmp(dirs[index], prefix, prefix_len))
		{
			dir_len -= (suf_len < dir_len) * suf_len;
			if (!ft_strncmp(dirs[index] + dir_len, suffix, suf_len))
			{
				if (node_create(get_cmd_list(), dirs[index]))
					return (-1);
				mode = 1;
				continue ;
			}
		}
		free(dirs[index]);
	}
	return (mode);
}

static char	insert_suffix(char **dirs, char *suffix, size_t suffix_len)
{
	size_t	dir_len;
	size_t	index;
	char	mode;

	index = 0;
	mode = 0;
	while (dirs[index])
	{
		dir_len = ft_strlen(dirs[index]);
		dir_len -= (suffix_len <= dir_len) * suffix_len;
		if (!ft_strncmp(dirs[index] + dir_len, suffix, suffix_len))
		{
			if (node_create(get_cmd_list(), dirs[index]))
				return (-1);
			mode = 1;
		}
		else
			free(dirs[index]);
		index++;
	}
	return (mode);
}

static char	insert_prefix(char **dirs, char *prefix, size_t prefix_len)
{
	size_t	index;
	char	mode;

	index = 0;
	mode = 0;
	while (dirs[index])
	{
		if (!ft_strncmp(dirs[index], prefix, prefix_len))
		{
			if (node_create(get_cmd_list(), dirs[index]))
				return (-1);
			mode = 1;
		}
		else
			free(dirs[index]);
		index++;
	}
	return (mode);
}

static char	insert_all(char **dirs)
{
	size_t	index;

	index = 0;
	while (dirs[index])
	{
		if (node_create(get_cmd_list(), dirs[index]))
			return (-1);
		index++;
	}
	return (index);
}

char	insert_dirs_to_list(char **dirs, char *prefix, char *suffix)
{
	char	mode;

	mode = 0;
	if (!prefix && !suffix)
		mode = insert_all(dirs);
	else if (prefix && !suffix)
		mode = insert_prefix(dirs, prefix, ft_strlen(prefix));
	else if (!prefix && suffix)
		mode = insert_suffix(dirs, suffix, ft_strlen(suffix));
	else if (prefix && suffix)
		mode = insert_ps(dirs, prefix, suffix, ft_strlen(suffix));
	free(prefix);
	free(suffix);
	free(dirs);
	return (mode);
}
