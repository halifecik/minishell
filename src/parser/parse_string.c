#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

bool	*inside_word(void)
{
	static bool	state = false;

	return (&state);
}

static void	check_word(char **end, char **start)
{
	if (*start < *end && node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	(*end)++;
	*inside_word() = false;
}

static void	create_node(char **end, char **start)
{
	if (!ft_strchr("|<>", **end))
	{
		if (node_create(get_cmd_list(), 0))
			return ((void)break_parse(end));
		*inside_word() = true;
	}
	*start = *end;
}

static void	check_char(char **current_char, char **start)
{
	if (!(*current_char))
		return ;
	if (**current_char == '\'')
		check_quotes(current_char, start);
	else if (**current_char == '\"')
		check_quotes(current_char, start);
	else if (**current_char == '$')
		check_environ(current_char, start, 0);
	else if (**current_char == '|')
		check_pipe(current_char, start);
	else if (**current_char == '>' || **current_char == '<')
		check_redirections(current_char, start);
	else if (**current_char == ' ' && *inside_word())
		check_word(current_char, start);
	else
		(*current_char)++;
}

char	*parse_string(char *input)
{
	char	*current_char;
	char	*start;

	*inside_word() = false;
	current_char = input;
	while (current_char && *current_char)
	{
		if (*current_char != ' ' && !*inside_word())
			create_node(&current_char, &start);
		check_char(&current_char, &start);
	}
	if (current_char && *inside_word())
		check_word(&current_char, &start);
	return (current_char);
}
