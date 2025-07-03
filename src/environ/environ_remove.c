/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:25:23 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:25:24 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

extern char	**environ;

static char	is_key_exist(size_t index, char *key, size_t key_len)
{
	if (!ft_strncmp(environ[index], key, key_len))
	{
		free(environ[index]);
		while (environ[index])
		{
			environ[index] = environ[(index) + 1];
			(index)++;
		}
		return (1);
	}
	return (0);
}

void	environ_remove(char *str)
{
	size_t	key_len;
	size_t	index;
	char	*key;

	if (!environ || !str || ft_strchr(str, '=') || !ft_isalpha(*str))
		return ;
	key = ft_strjoin(str, "=");
	if (!key)
		return ;
	key_len = ft_strlen(key) - 1;
	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		if (is_key_exist(index, key, key_len))
			break ;
		index++;
	}
	if (environ[index][0] == 63 && !ft_strncmp(str, "PWD", 4))
	{
		index++;
		is_key_exist(index, key, key_len);
	}
	free(key);
}
