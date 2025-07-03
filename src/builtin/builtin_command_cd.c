#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char	**environ;

static void	environ_set_pwd(char **pwd, size_t last_index)
{
	size_t	index;

	index = last_index;
	while (environ[index])
	{
		if (!ft_strncmp(environ[index], "PWD=", 4))
		{
			free(environ[index]);
			environ[index] = *pwd;
			return ;
		}
		index++;
	}
	environ[index + 1] = NULL;
	index--;
	while (environ[index] && environ[index][0] != 63)
	{
		environ[index + 1] = environ[index];
		index--;
	}
	environ[index + 1] = *pwd;
}

static char	environ_check_pwd(void)
{
	char	*pwd;
	char	*cwd;
	size_t	index;

	cwd = pwd_variable();
	if (!cwd)
		return (error_malloc());
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (error_malloc());
	index = 0;
	while (environ[index] && environ[index][0] != 63)
	{
		if (!ft_strncmp(environ[index], "PWD=", 4))
		{
			environ_append(pwd);
			free(pwd);
			return (0);
		}
		index++;
	}
	environ_set_pwd(&pwd, index);
	return (0);
}

static char	change_directory(char *path, char **oldpwd)
{
	if (chdir(path) != 0)
	{
		free(*oldpwd);
		write(STDERR_FILENO, "minishell: cd: ", 15);
		perror(path);
		set_exit_status_code(1);
		return (1);
	}
	if (*oldpwd)
		environ_append(*oldpwd);
	free(*oldpwd);
	return (environ_check_pwd());
}

static char	set_environ_and_cd(char *path)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = NULL;
	if (getenv("OLDPWD"))
	{
		cwd = getenv("PWD");
		if (!cwd)
			cwd = ft_strdup("");
		if (!cwd)
			return (error_malloc());
		oldpwd = ft_strjoin("OLDPWD=", cwd);
		if (cwd[0] == '\0')
			free(cwd);
	}
	if (change_directory(path, &oldpwd))
		return (1);
	return (0);
}

void	command_cd(t_list *args)
{
	char	*path;

	if (args && args->next)
	{
		write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
		set_exit_status_code(1);
		return ;
	}
	if (!args)
	{
		path = getenv("HOME");
		if (!path)
		{
			write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28);
			set_exit_status_code(1);
			return ;
		}
	}
	else
		path = args->value;
	if (set_environ_and_cd(path))
		return ;
	set_exit_status_code(0);
}
