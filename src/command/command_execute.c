/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:24:22 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:24:23 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

extern char	**environ;

static char	*add_slash(char *path, char *cmd, char *env_path)
{
	char	*full_path;

	if (!path)
		return (NULL);
	full_path = malloc(ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!full_path)
	{
		free(env_path);
		return (NULL);
	}
	ft_strncpy(full_path, path, ft_strlen(path));
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	return (full_path);
}

static t_uint8	search_path_and_call_execve(char **cmd_array)
{
	char	*env_path;
	char	*path;

	env_path = getenv("PATH");
	if (!env_path)
		return (error_child(cmd_array[0], 0));
	env_path = ft_strdup(env_path);
	if (!env_path)
		return (error_malloc());
	path = ft_strtok(env_path, ":");
	while (path)
	{
		path = add_slash(path, cmd_array[0], env_path);
		if (!path)
			return (error_malloc());
		if (execve(path, cmd_array, environ) == -1)
			free(path);
		path = ft_strtok(NULL, ":");
	}
	free(env_path);
	return (error_child(cmd_array[0], 1));
}

static t_uint8	call_execve(char **cmd_array)
{
	if (ft_strchr(cmd_array[0], '/'))
	{
		if (access(cmd_array[0], F_OK) == -1)
			return (error_child(cmd_array[0], 0));
		execve(cmd_array[0], cmd_array, environ);
		return (error_child(cmd_array[0], -1));
	}
	return (search_path_and_call_execve(cmd_array));
}

static void	child_execute(t_list **cmd_list)
{
	char	**cmd_array;
	t_uint8	exit_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd_array = list_to_array(cmd_list);
	if (!cmd_array)
		exit_status = error_malloc();
	else
		exit_status = call_execve(cmd_array);
	free(cmd_array);
	free_resources_and_exit(exit_status);
}

void	command_execute(char is_forked)
{
	pid_t	pid;

	if (is_forked == 1)
		child_execute(get_cmd_list());
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork() error");
		set_exit_status_code(11);
		return ;
	}
	if (pid == 0)
		child_execute(get_cmd_list());
	check_wait_status(pid);
}
