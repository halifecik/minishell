/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:21:23 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:21:24 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>
#include <dirent.h>

void	free_entries(char **entries, char **end)
{
	size_t	index;

	if (!entries)
		return ;
	index = 0;
	while (entries[index])
	{
		free(entries[index]);
		index++;
	}
	free(entries);
	if (*end)
		break_parse(end);
}

static int	compare_strcasecmp(const void *a, const void *b)
{
	const char	*s1;
	const char	*s2;
	char		c1;
	char		c2;

	s1 = *(const char **)a;
	s2 = *(const char **)b;
	while (*s1 && *s2)
	{
		c1 = ft_tolower((unsigned char)*s1);
		c2 = ft_tolower((unsigned char)*s2);
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		s1++;
		s2++;
	}
	return (ft_tolower((unsigned char)*s1) - ft_tolower((unsigned char)*s2));
}

static char	**memory_allocate(char **entries, size_t *capacity)
{
	char	**array;
	size_t	size;

	size = *capacity;
	if (*capacity == 0)
		*capacity = 8;
	else
		*capacity *= 2;
	array = malloc((*capacity + 1) * sizeof(char *));
	if (!array)
	{
		free_entries(entries, NULL);
		return (NULL);
	}
	while (size > 0)
	{
		size--;
		array[size] = entries[size];
	}
	free(entries);
	return (array);
}

static char	**resolve_and_sort(DIR *dir)
{
	struct dirent	*entry;
	char			**entries;
	size_t			capacity;
	size_t			count;

	count = 0;
	capacity = 0;
	entries = NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (capacity == count)
		{
			entries = memory_allocate(entries, &capacity);
			if (!entries)
				return (NULL);
		}
		if (*(entry->d_name) != '.')
			entries[count++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	quick_sort(entries, count, sizeof(char *), compare_strcasecmp);
	entries[count] = NULL;
	return (entries);
}

char	**resolve_dir_name(char **end)
{
	DIR		*dir;
	char	**dir_name;

	dir = opendir(".");
	if (!dir)
	{
		error_syscall("minishell: opendir() error", end);
		return (NULL);
	}
	dir_name = resolve_and_sort(dir);
	closedir(dir);
	if (!dir_name)
		break_parse(end);
	return (dir_name);
}
