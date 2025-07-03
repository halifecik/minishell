/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:26:35 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:26:36 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

static void	do_redirection(char **end, int fd_file, int rd_number)
{
	char	*rd_number_str;

	copy_fd_redirection(rd_number);
	if (dup2(fd_file, rd_number) == -1)
	{
		reset_fd_redirection();
		rd_number_str = ft_ltoa(rd_number);
		if (!rd_number_str)
		{
			break_parse(end);
			return ;
		}
		error_redirection(end, rd_number_str);
	}
	else if (*get_fd_redirection() == -1)
		*get_fd_redirection() = rd_number;
}

static int	redirection_file_open(char **end, char mode, char suffix)
{
	char	*file_name;
	int		fd_file;

	fd_file = 0;
	if (**end == '>')
		(*end)++;
	while (**end == ' ')
		(*end)++;
	file_name = sub_parser(end);
	if (!file_name)
		return (-1);
	if (mode == '>' && suffix == '>')
		fd_file = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (mode == '>')
		fd_file = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (mode == '<')
		fd_file = open(file_name, O_RDONLY);
	if (fd_file == -1)
	{
		error_redirection(end, file_name);
		return (-1);
	}
	free(file_name);
	return (fd_file);
}

static int	redirection_number(int prev_rd_number, char **end, char **start)
{
	long	rd_number;
	int		size;
	char	*str;

	size = *end - *start;
	str = *start;
	rd_number = 0;
	if (size < 11)
	{
		while (*str >= '0' && *str <= '9' && str < *end)
			rd_number = rd_number * 10 + (*str++ - '0');
	}
	if ((*str != '>' && *str != '<') || rd_number > INT_MAX || size > 10)
	{
		if (node_insert(get_cmd_list(), *start, size))
		{
			break_parse(end);
			return (-1);
		}
		return (prev_rd_number);
	}
	node_destroy_empty(get_cmd_list());
	return (rd_number);
}

static int	set_open_and_redirection(char **end, char mode)
{
	int		fd_file;
	char	suffix;

	(*end)++;
	suffix = **end;
	fd_file = -1;
	if (mode == '<' && suffix == '<')
	{
		fd_file = here_document_read(end);
		if (fd_file < 0)
			return (-1);
	}
	if (fd_file == -1)
	{
		fd_file = redirection_file_open(end, mode, suffix);
		if (fd_file == -1)
			return (-1);
	}
	return (fd_file);
}

void	check_redirections(char **end, char **start)
{
	int		rd_number;
	int		fd_file;
	char	mode;

	if (**end == '>')
		rd_number = STDOUT_FILENO;
	else if (**end == '<')
		rd_number = STDIN_FILENO;
	if (*start < *end)
		rd_number = redirection_number(rd_number, end, start);
	if (rd_number == -1)
		return ;
	mode = **end;
	fd_file = set_open_and_redirection(end, mode);
	if (fd_file == -1)
		return ;
	do_redirection(end, fd_file, rd_number);
	close(fd_file);
	*start = *end;
	*inside_word() = false;
}
