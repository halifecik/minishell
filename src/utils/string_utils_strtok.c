#include "string_utils.h"

static char	*ft_strtok_next(const char *delim, char **last)
{
	char		*start;
	char		*end;

	if (*last == NULL)
		return (NULL);
	start = *last;
	while (*start && ft_strchr(delim, *start))
		start++;
	if (*start == '\0')
	{
		*last = NULL;
		return (NULL);
	}
	end = start;
	while (*end && !ft_strchr(delim, *end))
		end++;
	if (*end != '\0')
	{
		*end = '\0';
		*last = end + 1;
	}
	else
		*last = NULL;
	return (start);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last;

	if (str != NULL)
		last = str;
	return (ft_strtok_next(delim, &last));
}
