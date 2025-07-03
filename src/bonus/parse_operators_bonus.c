/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operators_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:15 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:16 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

static int	set_prev_pipe_read_to_stdin(char **end)
{
	int	fd_stdin;

	if (*get_prev_pipe_read() == -1)
		return (0);
	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin == -1)
	{
		node_destroy_list(get_cmd_list());
		error_syscall("minishell: dup() error", end);
		return (-1);
	}
	if (dup2(*get_prev_pipe_read(), STDIN_FILENO) == -1)
	{
		node_destroy_list(get_cmd_list());
		error_syscall("minishell: dup2() error", end);
		close(fd_stdin);
		return (-1);
	}
	close_prev_pipe_read();
	return (fd_stdin);
}

void	check_operator_and(char **end, char **start)
{
	int	fd_stdin;

	if (*start < *end && node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	(*end)++;
	*start = ++(*end);
	fd_stdin = set_prev_pipe_read_to_stdin(end);
	if (fd_stdin == -1)
		return ;
	command_calls(get_cmd_list(), 0);
	node_destroy_list(get_cmd_list());
	if (get_exit_status_code() != 0)
		while (**end != '\0' && !(**end == '|' && *(*end + 1) == '|'))
			if (*(*end)++ == '(')
				*end = ft_strchr(*end, ')');
	if (fd_stdin > 0)
	{
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
	}
	*inside_word() = false;
}

void	check_operator_or(char **end, char **start)
{
	int	fd_stdin;

	if (*start < *end && node_insert(get_cmd_list(), *start, *end - *start))
		return ((void)break_parse(end));
	(*end)++;
	*start = ++(*end);
	fd_stdin = set_prev_pipe_read_to_stdin(end);
	if (fd_stdin == -1)
		return ;
	command_calls(get_cmd_list(), 0);
	node_destroy_list(get_cmd_list());
	if (get_exit_status_code() == 0)
		while (**end != '\0' && !(**end == '&' && *(*end + 1) == '&'))
			if (*(*end)++ == '(')
				*end = ft_strchr(*end, ')');
	if (fd_stdin > 0)
	{
		dup2(fd_stdin, STDIN_FILENO);
		close(fd_stdin);
	}
	*inside_word() = false;
}
