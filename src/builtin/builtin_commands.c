/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:22:57 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:22:58 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

extern char	**environ;

void	command_env(void)
{
	t_list	*current;
	size_t	index;

	current = (*get_cmd_list());
	if (current->next)
	{
		write(STDERR_FILENO, "env: invalid usage\n", 19);
		set_exit_status_code(125);
		return ;
	}
	index = 0;
	while (environ[index] && environ[index][0] != '?')
	{
		write(STDOUT_FILENO, environ[index], ft_strlen(environ[index]));
		write(STDOUT_FILENO, "\n", 1);
		index++;
	}
	set_exit_status_code(0);
}

void	command_unset(void)
{
	t_list	*current;

	current = (*get_cmd_list())->next;
	while (current)
	{
		environ_remove(current->value);
		current = current->next;
	}
	set_exit_status_code(0);
}

void	command_pwd(void)
{
	char	*cwd;

	cwd = pwd_variable();
	if (!cwd)
		return ;
	write(STDOUT_FILENO, cwd, ft_strlen(cwd));
	write(STDOUT_FILENO, "\n", 1);
	set_exit_status_code(0);
}

void	command_echo(t_list *args)
{
	char	*value;
	char	flag;

	flag = 1;
	while (args && !ft_strncmp(args->value, "-n", 2))
	{
		value = args->value + 1;
		while (*value == 'n')
			value++;
		if (*value == '\0')
			flag = 0;
		else
			break ;
		args = args->next;
	}
	while (args)
	{
		write(STDOUT_FILENO, args->value, ft_strlen(args->value));
		args = args->next;
		if (args)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag)
		write(STDOUT_FILENO, "\n", 1);
	set_exit_status_code(0);
}
