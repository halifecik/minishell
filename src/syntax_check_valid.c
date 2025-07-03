/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_valid.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:51:26 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:51:27 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

static void	syntax_error_write(char *token, unsigned int size)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, token, size);
	write(STDERR_FILENO, "'\n", 2);
	free(*get_input());
	*get_input() = NULL;
	set_exit_status_code(2);
}

static char	*syntax_error(char *str)
{
	if (*str == '|' && *(str + 1) == '|')
		syntax_error_write("||", 2);
	else if (*str == '|')
		syntax_error_write("|", 1);
	else if (*str == '&' && *(str + 1) == '&')
		syntax_error_write("&&", 2);
	else if (*str == '&')
		syntax_error_write("&", 1);
	return (NULL);
}

static char	*syntax_traverse(char *input, char delim)
{
	while (*input)
	{
		if (*input == '|' || *input == '&')
			break ;
		else if (!ft_strchr("|&", delim) && (*input == '<' || *input == '>'))
		{
			if (*(input + 1) == '<' || *(input + 1) == '>')
				syntax_error_write(input, 2);
			else
				syntax_error_write(input, 1);
			return (NULL);
		}
		else if (*input != ' ')
			return (syntax_check_valid(input));
		input++;
	}
	return (input);
}

static char	*syntax_find_delim(char *input)
{
	char	quote;

	if (*input == '|' || *input == '&')
		return (syntax_error(input));
	quote = 0;
	while (input && *input)
	{
		if (*input == '\'' || *input == '\"')
			quote = (quote == 0) * (*input) + (quote != *input) * quote;
		else if (quote == 0 && ft_strchr("|&<>", *input))
			return (input);
		input++;
	}
	if (quote != 0)
		syntax_error_write(&quote, 1);
	return (NULL);
}

char	*syntax_check_valid(char *input)
{
	char	*delim;

	delim = syntax_find_delim(input);
	if (!delim)
		return (NULL);
	input = delim;
	input++;
	if (*input == *delim)
		input++;
	else if (*delim == '&')
		return (syntax_error(delim));
	input = syntax_traverse(input, *delim);
	if (!input)
		return (NULL);
	if (*input == '\0' && ft_strchr("<>", *delim))
		syntax_error_write("newline", 7);
	else if (ft_strchr("|&<>", *delim))
	{
		if (*input == '|' || *input == '&')
			delim = input;
		syntax_error(delim);
	}
	return (NULL);
}
