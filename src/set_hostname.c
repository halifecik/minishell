#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

static void	hostname_remove_newline(char *buffer)
{
	char	*newline;

	newline = buffer;
	while (*newline != '\0')
	{
		if (*newline == '\n' || *newline == '.')
		{
			*newline = '\0';
			return ;
		}
		newline++;
	}
}

static char	*hostname_read(ssize_t fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	size_t	size;

	size = 128;
	buffer = (char *)malloc(size);
	if (!buffer)
	{
		close(fd);
		error_malloc();
		return (NULL);
	}
	bytes_read = read(fd, buffer, size - 1);
	close(fd);
	if (bytes_read == -1)
	{
		perror("minishell: Error reading from /etc/hostname");
		free(buffer);
		set_exit_status_code(1);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

static ssize_t	hostname_open(void)
{
	ssize_t	fd;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: Error opening /etc/hostname");
		set_exit_status_code(1);
		return (-1);
	}
	return (fd);
}

char	*set_hostname(void)
{
	char	*buffer;
	ssize_t	fd;

	fd = hostname_open();
	if (fd == -1)
		return (ft_strdup("(null)"));
	buffer = hostname_read(fd);
	if (!buffer)
		return (ft_strdup("(null)"));
	hostname_remove_newline(buffer);
	return (buffer);
}
