/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:24:15 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:45:45 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>

t_uint8	error_child(char *cmd, char mode)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	if (mode == -1)
	{
		if (access(cmd, X_OK) == -1)
			write(STDERR_FILENO, ": Permission denied\n", 20);
		else
			write(STDERR_FILENO, ": Is a directory\n", 17);
		return (126);
	}
	else if (mode == 0)
		write(STDERR_FILENO, ": No such file or directory\n", 28);
	else if (mode == 1)
		write(STDERR_FILENO, ": command not found\n", 20);
	return (127);
}

void	error_syscall(char *msg, char **end)
{
	perror(msg);
	close_prev_pipe_read();
	node_destroy_list(get_cmd_list());
	set_exit_status_code(11);
	if (*end)
		*end = NULL;
}

void	check_wait_status(pid_t pid)
{
	int	exit_status;

	waitpid(pid, &exit_status, 0);
	if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			set_exit_status_code(131);
		}
		else if (WTERMSIG(exit_status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			set_exit_status_code(130);
		}
	}
	else if (WIFEXITED(exit_status))
		set_exit_status_code(WEXITSTATUS(exit_status));
}
