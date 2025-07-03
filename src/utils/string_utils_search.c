#include "string_utils.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (unsigned char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char	*occurance;

	occurance = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			occurance = (char *)s;
		s++;
	}
	if (*s == (unsigned char)c)
		occurance = (char *)s;
	return (occurance);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && n > 1)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
