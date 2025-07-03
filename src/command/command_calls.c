#include "minishell.h"

static char	builtin_calls(t_list **cmd_list)
{
	char	*cmd;

	cmd = (*cmd_list)->value;
	if (!ft_strncmp(cmd, "echo", 5))
		command_echo((*cmd_list)->next);
	else if (!ft_strncmp(cmd, "cd", 3))
		command_cd((*cmd_list)->next);
	else if (!ft_strncmp(cmd, "pwd", 4))
		command_pwd();
	else if (!ft_strncmp(cmd, "export", 7))
		command_export(*cmd_list);
	else if (!ft_strncmp(cmd, "unset", 6))
		command_unset();
	else if (!ft_strncmp(cmd, "env", 4))
		command_env();
	else if (!ft_strncmp(cmd, "exit", 5))
		command_exit();
	else
		return (1);
	return (0);
}

void	command_calls(t_list **cmd_list, char is_forked)
{
	if (!(*cmd_list))
	{
		reset_fd_redirection();
		return ;
	}
	if (builtin_calls(cmd_list))
		command_execute(is_forked);
	reset_fd_redirection();
}
