#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

static void	error_end_of_file(char *limiter, size_t line_number)
{
	char	*line_number_str;

	line_number_str = NULL;
	write(STDERR_FILENO, "\n", 1);
	write(STDERR_FILENO, "minishell: warning: here-document at line ", 42);
	line_number_str = ft_ltoa(line_number);
	if (line_number_str)
		write(STDERR_FILENO, line_number_str, ft_strlen(line_number_str));
	write(STDERR_FILENO, " delimited by end-of-file (wanted `", 35);
	write(STDERR_FILENO, limiter, (ft_strlen(limiter) - 1));
	write(STDERR_FILENO, "')\n", 3);
	free(line_number_str);
	set_exit_status_code(1);
}

static char	*find_limiter(char **end)
{
	char	*limiter;
	char	*start;
	size_t	size;

	if (**end == '<')
		(*end)++;
	while (**end == ' ')
		(*end)++;
	start = *end;
	while (**end != ' ' && **end != '\0' && **end != '|')
		(*end)++;
	size = *end - start;
	limiter = malloc(size + 2);
	if (!limiter)
	{
		break_parse(end);
		return (NULL);
	}
	ft_strncpy(limiter, start, size);
	limiter[size] = '\n';
	limiter[size + 1] = '\0';
	return (limiter);
}

static void	call_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	set_exit_status_code(130);
	node_destroy_list(get_cmd_list());
	write(STDOUT_FILENO, "\n", 1);
	close(STDIN_FILENO);
}

static void	read_from_stdin(int fd_pipe[2], char *limiter)
{
	const size_t	limiter_size = ft_strlen(limiter);
	size_t			line_number;
	char			*line;

	line_number = 1;
	line = NULL;
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line && isatty(STDIN_FILENO))
			error_end_of_file(limiter, line_number);
		if (!line || !ft_strncmp(line, limiter, limiter_size))
			break ;
		line_number += ft_strlen(line);
		write(fd_pipe[1], line, ft_strlen(line));
		free(line);
	}
	close(fd_pipe[1]);
	free(line);
	free(limiter);
	get_next_line(-1);
}

int	here_document_read(char **end)
{
	char	*limiter;
	int		fd_pipe[2];
	int		fd_stdin;

	limiter = find_limiter(end);
	if (!limiter)
		return (-1);
	if (pipe(fd_pipe) == -1)
	{
		node_destroy_list(get_cmd_list());
		*end = NULL;
		free(limiter);
		perror("minishell: pipe() error");
		return (-1);
	}
	signal(SIGINT, call_sigint);
	fd_stdin = dup(STDIN_FILENO);
	read_from_stdin(fd_pipe, limiter);
	if (!isatty(STDIN_FILENO))
		dup2(fd_stdin, STDIN_FILENO);
	close(fd_stdin);
	signal(SIGINT, SIG_IGN);
	return (fd_pipe[0]);
}
