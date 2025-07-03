/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_command_export.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:22:56 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:23:04 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

extern char	**environ;

static void	write_output(char *str)
{
	char	*start;
	char	*end;

	start = str;
	end = ft_strchr(start, '=');
	end++;
	write(STDOUT_FILENO, "declare -x ", 11);
	write(STDOUT_FILENO, start, end - start);
	start = end;
	end = ft_strchr(end, '\0');
	write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, start, end - start);
	write(STDOUT_FILENO, "\"", 1);
	write(STDOUT_FILENO, "\n", 1);
}

static int	compare_strings(const void *a, const void *b)
{
	const char	*s1;
	const char	*s2;

	s1 = *(const char **)a;
	s2 = *(const char **)b;
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

static char	**duplicate_and_sort(void)
{
	char	**sorted;
	size_t	index;

	index = 0;
	while (environ[index] && environ[index][0] != 63)
		index++;
	sorted = malloc(sizeof(char *) * (index + 1));
	if (!sorted)
	{
		error_malloc();
		return (NULL);
	}
	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		sorted[index] = environ[index];
		index++;
	}
	quick_sort(sorted, index, sizeof(char *), compare_strings);
	sorted[index] = NULL;
	return (sorted);
}

static void	environ_sorted_print(void)
{
	size_t	index;
	char	**sorted;

	sorted = duplicate_and_sort();
	if (!sorted)
		return ;
	index = 0;
	while (sorted[index])
	{
		if (sorted[index][0] != '_')
			write_output(sorted[index]);
		index++;
	}
	free(sorted);
	set_exit_status_code(0);
}

void	command_export(t_list *cmd_list)
{
	t_list	*current;
	t_uint8	exit_code;

	current = cmd_list->next;
	if (!current)
		environ_sorted_print();
	exit_code = 0;
	while (current)
	{
		environ_append(current->value);
		current = current->next;
		if (get_exit_status_code())
			exit_code = 1;
	}
	if (exit_code)
		set_exit_status_code(1);
}
