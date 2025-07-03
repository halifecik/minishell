/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:18 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:26:19 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static void	search_environ(char **end, char **start, char in_quotes)
{
	size_t	size;
	char	*env;
	char	*var;

	size = *end - *start;
	var = malloc(size + 1);
	if (!var)
		return ((void)break_parse(end));
	ft_strncpy(var, *start, size);
	var[size] = '\0';
	env = getenv(var);
	free(var);
	if (env && node_insert(get_cmd_list(), env, ft_strlen(env)))
		return ((void)break_parse(end));
	else if (!env && in_quotes == 0)
		node_destroy_empty(get_cmd_list());
	*start = *end;
}

void	check_environ(char **end, char **start, char in_quotes)
{
	if (*start < *end && node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	*start = ++(*end);
	while (ft_isalpha(**start) && ft_isalnum(**end))
		(*end)++;
	if (*start == *end && (**end == '?' || ft_isalnum(**start)))
		(*end)++;
	if (*start == *end)
	{
		if (**start == '\'' || **start == '\"')
			return ;
		if (node_insert(get_cmd_list(), "$", 1))
			break_parse(end);
		return ;
	}
	search_environ(end, start, in_quotes);
}
