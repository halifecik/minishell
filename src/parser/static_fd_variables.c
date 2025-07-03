#include "minishell.h"

#include <unistd.h>

//static variable for save prev fd_pipe[0]
int	*get_prev_pipe_read(void)
{
	static int	fd_prev_read = -1;

	return (&fd_prev_read);
}

void	close_prev_pipe_read(void)
{
	int	fd_prev_pipe_read;

	fd_prev_pipe_read = *get_prev_pipe_read();
	if (fd_prev_pipe_read != -1)
	{
		close(fd_prev_pipe_read);
		*get_prev_pipe_read() = -1;
	}
}

//static variable for save redirection fds
int	*get_fd_redirection(void)
{
	static int	fd_redirection = -1;

	return (&fd_redirection);
}

void	copy_fd_redirection(int rd_number)
{
	int	fd_redirection;

	fd_redirection = *get_fd_redirection();
	if (fd_redirection == -1)
		*get_fd_redirection() = dup(rd_number);
}

void	reset_fd_redirection(void)
{
	int	fd_redirection;

	fd_redirection = *get_fd_redirection();
	if (fd_redirection != -1)
	{
		if (!isatty(STDIN_FILENO))
			dup2(fd_redirection, STDIN_FILENO);
		else if (!isatty(STDOUT_FILENO))
			dup2(fd_redirection, STDOUT_FILENO);
		else if (!isatty(STDERR_FILENO))
			dup2(fd_redirection, STDERR_FILENO);
		close(fd_redirection);
		*get_fd_redirection() = -1;
	}
}
