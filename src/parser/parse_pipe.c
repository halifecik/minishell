#include "minishell.h"

#include <unistd.h>

static char	search_left_pipe(char *current_char)
{
	char	*pipe_char;
	char	*quote_char;
	bool	inside_quote;

	pipe_char = ft_strchr(current_char, '|');
	if (!pipe_char)
		return (0);
	inside_quote = false;
	while (current_char < pipe_char)
	{
		if (*current_char == '\'' || *current_char == '\"')
		{
			inside_quote = !inside_quote;
			quote_char = current_char;
		}
		current_char++;
	}
	if (inside_quote)
	{
		quote_char = ft_strchr(pipe_char, *quote_char);
		if (quote_char)
			return (search_left_pipe(quote_char + 1));
	}
	return (1);
}

static void	execute_pipe(char **end)
{
	create_child_process(end);
	node_destroy_list(get_cmd_list());
	*inside_word() = false;
	if (!(*end) || search_left_pipe(*end))
		return ;
	if (!parse_string(*end))
	{
		*end = NULL;
		return ;
	}
	create_last_child_process(end);
	node_destroy_list(get_cmd_list());
	*end = NULL;
}

void	check_pipe(char **end, char **start)
{
	if (*start < *end && node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	*start = ++(*end);
	while (**end)
	{
		if (**end == '|')
			break ;
		if (**end != ' ')
		{
			execute_pipe(end);
			return ;
		}
		(*end)++;
	}
	if (**start == '|')
		error_syntax(end, "||");
	else
		error_syntax(end, "|");
	close_prev_pipe_read();
}
