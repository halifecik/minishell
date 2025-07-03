/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:33 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:26:34 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	check_quotes_closed(char **end, char **start)
{
	char	quote;

	quote = **end;
	if (**start != quote && node_insert(get_cmd_list(), *start, *end - *start))
	{
		break_parse(end);
		return (0);
	}
	*start = ++(*end);
	*end = ft_strchr(*end, quote);
	if (!(*end))
	{
		error_syntax(end, &quote);
		return (0);
	}
	return (quote);
}

void	check_quotes(char **end, char **start)
{
	char	quote;

	quote = check_quotes_closed(end, start);
	if (quote == 0)
		return ;
	**end = '\0';
	if (quote == '\"')
	{
		*end = ft_strchr(*start, '$');
		while (*end)
		{
			check_environ(end, start, 1);
			if (!(*end))
				return ;
			*end = ft_strchr(*start, '$');
		}
	}
	*end = ft_strchr(*start, '\0');
	(*end)++;
	if (node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	*start = *end;
}
