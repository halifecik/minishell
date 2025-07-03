/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:22:55 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:22:56 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>

static unsigned char	error_argument(void)
{
	char	*argument;

	argument = (*get_cmd_list())->next->value;
	write(STDERR_FILENO, "minishell: exit: ", 17);
	write(STDERR_FILENO, argument, ft_strlen(argument));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	free_resources_and_exit(2);
	return (0);
}

void	command_exit(void)
{
	t_uint8	exit_code;
	t_list	*arg_list;

	write(STDOUT_FILENO, "exit\n", 5);
	arg_list = (*get_cmd_list())->next;
	if (arg_list)
	{
		exit_code = (t_uint8)ft_atol(arg_list->value, error_argument);
		if (arg_list->next)
		{
			write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
			if (get_exit_status_code() == 0)
				set_exit_status_code(1);
			return ;
		}
	}
	else
		exit_code = get_exit_status_code();
	free_resources_and_exit(exit_code);
}
