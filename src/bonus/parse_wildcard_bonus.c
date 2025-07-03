/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_wildcard_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:19 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:20 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static char	*find_prefix(char **end, char **start)
{
	char	*prefix;
	size_t	size;

	prefix = NULL;
	size = *end - *start;
	prefix = malloc(size + 1);
	if (!prefix)
		return (NULL);
	ft_strncpy(prefix, *start, size);
	prefix[size] = '\0';
	node_destroy_empty(get_cmd_list());
	return (prefix);
}

static char	*find_suffix(char **end)
{
	char	*start;
	char	*suffix;
	size_t	size;

	while (**end == '*')
		(*end)++;
	start = *end;
	while (*end)
	{
		if (**end == '\0' || ft_strchr(" |&<>", **end))
			break ;
		(*end)++;
	}
	if (start == *end)
		return ("");
	size = *end - start;
	suffix = malloc(size + 1);
	if (!suffix)
		return (NULL);
	ft_strncpy(suffix, start, size);
	suffix[size] = '\0';
	return (suffix);
}

static char	prefix_and_suffix(char **end, char **start, char **pre, char **suf)
{
	*pre = NULL;
	*suf = NULL;
	if (*start < *end)
	{
		*pre = find_prefix(end, start);
		if (!(*pre))
			return (1);
	}
	*suf = find_suffix(end);
	if (!(*suf))
	{
		free(*pre);
		*pre = NULL;
		return (1);
	}
	if (**suf == '\0')
		*suf = NULL;
	return (0);
}

void	check_wildcard(char **end, char **start)
{
	char	**sorted_dir;
	char	*prefix;
	char	*suffix;
	char	inserted;

	sorted_dir = resolve_dir_name(end);
	if (!sorted_dir)
		return ;
	if (prefix_and_suffix(end, start, &prefix, &suffix))
		return ((void)free_entries(end, sorted_dir));
	inserted = insert_dirs_to_list(sorted_dir, prefix, suffix);
	if (inserted == -1)
		return ((void)break_parse(end));
	if (inserted == 0)
	{
		node_create(get_cmd_list(), 0);
		node_insert(get_cmd_list(), *start, *end - *start);
	}
	*start = *end;
	*inside_word() = false;
}
