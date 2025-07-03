#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

static char	*set_cwd(char *full_cwd)
{
	char	*home;
	char	*cwd;

	if (!full_cwd)
		return (NULL);
	home = getenv("HOME");
	if (home && !ft_strncmp(full_cwd, home, ft_strlen(home) + 1))
	{
		free(full_cwd);
		return (ft_strdup("~"));
	}
	cwd = ft_strrchr(full_cwd, '/');
	if (cwd && cwd[1] != '\0')
		cwd = ft_strdup(cwd + 1);
	else
		cwd = ft_strdup(full_cwd);
	free(full_cwd);
	return (cwd);
}

static char	*merge_prompt(char *s1, char *s2, char *s3, char *s4)
{
	char	*merged;
	size_t	size;

	if (!s3 || !s4)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + ft_strlen(s4) + 1;
	merged = (char *)malloc(size);
	if (!merged)
	{
		error_malloc();
		return (NULL);
	}
	ft_strncpy(merged, s1, ft_strlen(s1));
	ft_strcat(merged, s2);
	ft_strcat(merged, s3);
	ft_strcat(merged, s4);
	return (merged);
}

static char	*get_half_prompt(char mode)
{
	static char	*half_prompt = NULL;
	static char	*user_name = NULL;
	static char	*host_name = NULL;

	if (half_prompt || mode == 1)
		return (half_prompt);
	if (!user_name)
	{
		user_name = getenv("USER");
		if (!user_name)
			return (NULL);
	}
	if (!host_name)
		host_name = set_hostname();
	half_prompt = merge_prompt("[", user_name, "@", host_name);
	free(host_name);
	host_name = NULL;
	if (!half_prompt)
	{
		free(half_prompt);
		half_prompt = NULL;
		return (NULL);
	}
	return (half_prompt);
}

char	*set_prompt(void)
{
	char	**prompt;
	char	*half_prompt;
	char	*cwd;

	prompt = get_prompt();
	if (*prompt)
	{
		free(*prompt);
		*prompt = NULL;
	}
	half_prompt = get_half_prompt(0);
	if (!half_prompt)
		return ("[(null)]$ ");
	cwd = set_cwd(getcwd(NULL, 0));
	if (!cwd)
		cwd = ft_strdup(".");
	cwd = ft_strmjoin(cwd, " ");
	cwd = ft_strmjoin(cwd, getenv("?"));
	if (!cwd)
		cwd = ft_strdup("(null)");
	*prompt = merge_prompt(half_prompt, " ", cwd, "]# ");
	free(cwd);
	return (*prompt);
}

void	free_full_prompt(void)
{
	free(*get_prompt());
	free(get_half_prompt(1));
}
