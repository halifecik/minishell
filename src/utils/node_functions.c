/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:49:27 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:49:32 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"

#include <stdlib.h>

void	node_destroy_list(t_list **head)
{
	t_list	*current;

	if (*head == NULL)
		return ;
	current = *head;
	while (current)
	{
		free(current->value);
		current = current->next;
		free(*head);
		*head = current;
	}
	*head = NULL;
}

char	node_create(t_list **head, char *value)
{
	t_list	*current;
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (1);
	new_node->value = value;
	new_node->next = NULL;
	if (*head)
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	else
		*head = new_node;
	return (0);
}

char	node_insert(t_list **head, char *str, size_t len)
{
	t_list	*current;
	char	*value;

	if (!(*head))
		return (0);
	current = *head;
	while (current && current->next)
		current = current->next;
	value = malloc(len + 1);
	if (!value)
		return (1);
	value = ft_strncpy(value, str, len);
	value[len] = '\0';
	if (current->value)
	{
		current->value = ft_strmjoin(current->value, value);
		free(value);
	}
	else
		current->value = value;
	return (0);
}

void	node_destroy_empty(t_list **head)
{
	t_list	*prev;
	t_list	*current;

	if (!(*head))
		return ;
	prev = NULL;
	current = *head;
	while (current->next)
	{
		prev = current;
		current = current->next;
	}
	if (!current->value)
	{
		if (prev)
			prev->next = NULL;
		else
			*head = NULL;
		free(current->value);
		free(current);
	}
}
