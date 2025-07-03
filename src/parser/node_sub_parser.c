/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_sub_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:16 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:26:17 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

static char	*find_first_word(char **end, char *temp)
{
	char		quote;

	quote = 0;
	while (end && *end)
	{
		if (**end == '\'' || **end == '\"')
		{
			if (quote == 0)
				quote = **end;
			else if (quote && quote == **end)
				quote = 0;
		}
		else if (quote == 0 && ft_strchr(" |&<>", **end))
			break ;
		(*end)++;
	}
	*temp = **end;
	return (*end);
}

static char	*create_sub_list(char *start)
{
	t_list	*cmd_list;
	t_list	*sub_list;
	char	*value;

	sub_list = NULL;
	cmd_list = *get_cmd_list();
	*get_cmd_list() = NULL;
	if (!parse_string(start))
	{
		node_destroy_list(&cmd_list);
		return (NULL);
	}
	sub_list = *get_cmd_list();
	*get_cmd_list() = cmd_list;
	if (!sub_list)
		return (ft_strdup(""));
	value = sub_list->value;
	free(sub_list);
	return (value);
}

char	*sub_parser(char **input)
{
	char	*value;
	char	*start;
	char	temp;

	start = *input;
	if (!find_first_word(input, &temp))
		return (NULL);
	**input = '\0';
	value = create_sub_list(start);
	if (!value)
	{
		*input = NULL;
		return (NULL);
	}
	**input = temp;
	return (value);
}
