/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parentheses_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:17 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:18 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <sys/wait.h>

static void	execute_subshell(char **end, char **start)
{
	**end = '\0';
	(*start)++;
	parse_string(*start);
	command_calls(get_cmd_list(), 0);
	node_destroy_list(get_cmd_list());
	free_resources_and_exit(get_exit_status_code());
}

void	check_parentheses(char **end, char **start)
{
	char	*redir;
	char	*s;
	pid_t	pid;
	int		status;

	*end = ft_strchr(*end, ')');
	if (!(*end))
		return ((void)error_syntax(end, ")"));
	redir = *end + 1;
	s = *start;
	while (*redir && *redir == ' ')
		redir++;
	if (*redir == '>' || *redir == '<')
		check_redirections(&redir, &s);
	while (wait(NULL) > 0)
		;
	pid = fork();
	if (pid == -1)
		return ((void)error_syscall("minishell: fork() error", end));
	if (pid == 0)
		execute_subshell(end, start);
	wait(&status);
	set_exit_status_code(WEXITSTATUS(status));
	*end = redir;
	*start = *end;
}
