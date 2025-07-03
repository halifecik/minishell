/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_valid_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:21 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:22 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

static char	*syntax_error(char *token, unsigned int size)
{
	if (*token == '|' && *(token + 1) == '|')
		size = 2;
	else if (*token == '|')
		size = 1;
	else if (*token == '&' && *(token + 1) == '&')
		size = 2;
	else if (*token == '&')
		size = 1;
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, token, size);
	write(STDERR_FILENO, "'\n", 2);
	free(*get_input());
	*get_input() = NULL;
	set_exit_status_code(2);
	return (NULL);
}

static char	*syntax_traverse(char *input, char delim, char **start)
{
	if (**start != '(')
		*start = input;
	while (input && *input)
	{
		if (*input == '|' || *input == '&')
			break ;
		else if (!ft_strchr("|&", delim) && ft_strchr("(<>", *input))
		{
			if (*input != '(' && ft_strchr("<>", *(input + 1)))
				syntax_error(input, 2);
			else
				syntax_error(input, 1);
			return (NULL);
		}
		else if (**start == '(' && *input == ')' && ft_strchr("|&<>", delim))
			return (syntax_error(")", 1));
		else if (*input != ' ')
			return (syntax_check_valid(input));
		input++;
	}
	return (input);
}

static char	*syntax_check_paren(char *input, char **start)
{
	if (*input == '(')
	{
		while (*start < input)
			if (*(*start)++ != ' ')
				return (syntax_error("(", 1));
		if (*(input + 1) == '|' || *(input + 1) == '&')
			return (syntax_error(input + 1, 0));
	}
	else if (**start == '(' && *input == ')')
	{
		(*start)++;
		while (*start < input && **start == ' ')
			(*start)++;
		if (**start == *input)
			return (syntax_error(")", 1));
		*start = input;
	}
	else if (**start == ')' && !ft_strchr(" |&<>", *input))
	{
		*start = input;
		while (*input && !ft_strchr(" |&<>", *input))
			input++;
		return (syntax_error(*start, input - *start));
	}
	return ("");
}

static char	*syntax_find_delim(char *input, char **start)
{
	char	quote;

	if (*input == '|' || *input == '&')
		return (syntax_error(input, 0));
	quote = 0;
	while (input && *input)
	{
		if (*input == '\'' || *input == '\"')
			quote = (quote == 0) * (*input) + (quote != *input) * quote;
		else if (quote == 0 && ft_strchr("|&<>", *input))
			return (input);
		else if (quote == 0)
		{
			if (**start != '(' && *input == ')')
				return (syntax_error(")", 1));
			if (!syntax_check_paren(input, start))
				return (NULL);
		}
		input++;
	}
	if (quote != 0)
		syntax_error(&quote, 1);
	else if (*start && **start == '(' && *input == '\0')
		syntax_error("(", 1);
	return (NULL);
}

char	*syntax_check_valid(char *input)
{
	static char	*start = NULL;
	char		*delim;

	if (!start)
		start = input;
	delim = syntax_find_delim(input, &start);
	if (!delim)
		return (start = NULL);
	input = delim + 1;
	if (*input == *delim)
		input++;
	else if (*delim == '&')
		return (start = NULL, syntax_error(delim, 0));
	input = syntax_traverse(input, *delim, &start);
	if (!input)
		return (start = NULL);
	if (*input == '\0' && ft_strchr("<>", *delim))
		syntax_error("newline", 7);
	else if (ft_strchr("|&<>", *delim))
	{
		if (*input == '|' || *input == '&')
			delim = input;
		syntax_error(delim, 0);
	}
	return (start = NULL);
}
