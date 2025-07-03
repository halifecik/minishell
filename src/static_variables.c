/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:51:27 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:51:28 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <unistd.h>
#include <stdlib.h>

t_list	**get_cmd_list(void)
{
	static t_list	*cmd_list = NULL;

	return (&cmd_list);
}

char	**get_input(void)
{
	static char	*input = NULL;

	return (&input);
}

char	**get_prompt(void)
{
	static char	*prompt = NULL;

	return (&prompt);
}

char	*pwd_variable(void)
{
	static char	*pwd = NULL;
	char		*temp;

	temp = getcwd(NULL, 0);
	if (temp)
	{
		free(pwd);
		pwd = temp;
	}
	return (pwd);
}
