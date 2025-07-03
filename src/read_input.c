/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:51:37 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:51:37 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	call_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	set_exit_status_code(130);
	rl_replace_line("", 0);
	close(STDIN_FILENO);
}

static void	read_signal_received(int fd_stdin)
{
	char	**input;

	input = get_input();
	if (!*input && !isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, "\n", 1);
		while (!*input && !isatty(STDIN_FILENO))
		{
			dup2(fd_stdin, STDIN_FILENO);
			*input = readline(set_prompt());
		}
	}
	if (!*input && errno == 0)
	{
		write(STDERR_FILENO, "exit\n", 5);
		close(fd_stdin);
		free_resources_and_exit(get_exit_status_code());
	}
}

void	read_input(void)
{
	char	**input;
	int		fd_stdin;

	signal(SIGINT, call_sigint);
	signal(SIGQUIT, SIG_IGN);
	input = get_input();
	if (*input)
		free(*input);
	fd_stdin = dup(STDIN_FILENO);
	*input = readline(set_prompt());
	if (!*input)
		read_signal_received(fd_stdin);
	close(fd_stdin);
	if (*input && **input != '\0')
		add_history(*input);
	signal(SIGINT, SIG_IGN);
	syntax_check_valid(*input);
}
