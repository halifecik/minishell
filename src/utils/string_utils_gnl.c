#include "string_utils.h"

#include <unistd.h>
#include <stdlib.h>

static void	ft_return_line(char **remainder, char **line)
{
	char	*new_remainder;

	if (*line)
	{
		new_remainder = ft_strdup(*remainder + ft_strlen(*line));
		free(*remainder);
		*remainder = new_remainder;
	}
	else if (*remainder)
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
	}
}

static char	*ft_read_line(char **remainder)
{
	char	*newline;
	char	*line;

	if (!*remainder)
		return (NULL);
	newline = ft_strchr(*remainder, '\n');
	if (newline != NULL)
	{
		line = malloc(newline - *remainder + 2);
		if (!line)
			return (NULL);
		ft_strncpy(line, *remainder, newline - *remainder + 1);
		return (line);
	}
	return (NULL);
}

static ssize_t	ft_get_remainder(int fd, char **remainder)
{
	ssize_t	bytes_read;
	char	*buffer;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (0);
	}
	buffer[bytes_read] = '\0';
	if (*remainder)
		*remainder = ft_strmjoin(*remainder, buffer);
	else
		*remainder = ft_strdup(buffer);
	free(buffer);
	if (!(*remainder))
		return (-1);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;
	ssize_t		readed_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	readed_bytes = ft_get_remainder(fd, &remainder);
	if (readed_bytes <= 0 && (!remainder || remainder[0] == '\0'))
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}
	line = ft_read_line(&remainder);
	while (!line && readed_bytes > 0)
	{
		readed_bytes = ft_get_remainder(fd, &remainder);
		line = ft_read_line(&remainder);
	}
	ft_return_line(&remainder, &line);
	return (line);
}
