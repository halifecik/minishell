/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute_pipeline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:24:28 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:24:29 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

static char	set_prev_pipe_read_to_stdin(void)
{
	if (*get_prev_pipe_read() == -1)
		return (0);
	if (dup2(*get_prev_pipe_read(), STDIN_FILENO) == -1)
	{
		error_syscall("minishell: dup2() error", NULL);
		return (1);
	}
	close_prev_pipe_read();
	return (0);
}

static void	call_child_process(int fd_pipe[2])
{
	close(fd_pipe[0]);
	if (set_prev_pipe_read_to_stdin())
	{
		close(fd_pipe[1]);
		free_resources_and_exit(11);
	}
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2() error");
		close(fd_pipe[1]);
		free_resources_and_exit(11);
	}
	close(fd_pipe[1]);
	command_calls(get_cmd_list(), 1);
	free_resources_and_exit(get_exit_status_code());
}

static void	execute_redirection(char **end)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		error_syscall("minishell: fork() error", end);
		return ;
	}
	if (pid == 0)
	{
		set_prev_pipe_read_to_stdin();
		command_calls(get_cmd_list(), 1);
		free_resources_and_exit(get_exit_status_code());
	}
	close_prev_pipe_read();
	reset_fd_redirection();
}

void	create_child_process(char **end)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (*get_fd_redirection() != -1 && isatty(STDIN_FILENO))
		return ((void)execute_redirection(end));
	if (pipe(fd_pipe) == -1)
	{
		error_syscall("minishell: pipe() error", end);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		error_syscall("minishell: fork() error", end);
		return ;
	}
	if (pid == 0)
		call_child_process(fd_pipe);
	close_prev_pipe_read();
	close(fd_pipe[1]);
	*get_prev_pipe_read() = fd_pipe[0];
	reset_fd_redirection();
}

void	create_last_child_process(char **end)
{
	int		child_get_sigint;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		error_syscall("minishell: fork() error", end);
		return ;
	}
	if (pid == 0)
	{
		if (set_prev_pipe_read_to_stdin())
			free_resources_and_exit(11);
		command_calls(get_cmd_list(), 1);
		free_resources_and_exit(get_exit_status_code());
	}
	close_prev_pipe_read();
	reset_fd_redirection();
	check_wait_status(pid);
	child_get_sigint = 0;
	while (wait(&child_get_sigint) != -1)
		if (WTERMSIG(child_get_sigint) == SIGINT)
			child_get_sigint = -1;
	if (child_get_sigint == -1 && get_exit_status_code() != 130)
		write(STDOUT_FILENO, "\n", 1);
}
