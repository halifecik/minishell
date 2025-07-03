/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:45 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:26:46 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void	error_redirection(char **end, char *str)
{
	write(STDERR_FILENO, "minishell: ", 11);
	perror(str);
	free(str);
	node_destroy_list(get_cmd_list());
	set_exit_status_code(1);
	while (**end != '\0' && **end != '|')
		(*end)++;
}

void	error_syntax(char **end, char *token)
{
	node_destroy_list(get_cmd_list());
	*end = NULL;
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "'\n", 2);
	set_exit_status_code(2);
}

void	break_parse(char **end)
{
	node_destroy_list(get_cmd_list());
	error_malloc();
	*end = NULL;
}
