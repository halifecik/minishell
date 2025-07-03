/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_quick_sort.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:49:08 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:49:09 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string_utils.h"

#include <stdlib.h>

static void	swap(void *a, void *b, size_t size)
{
	void	*temp;

	temp = malloc(size);
	if (!temp)
		return ;
	ft_memcpy(temp, a, size);
	ft_memcpy(a, b, size);
	ft_memcpy(b, temp, size);
	free(temp);
}

static void	*partition(void *base, size_t n_items, size_t size,
						int (*compar)(const void *, const void *))
{
	char	*arr;
	void	*pivot;
	int		i;
	size_t	j;

	arr = (char *)base;
	pivot = arr + (n_items - 1) * size;
	i = -1;
	j = 0;
	while (j < n_items - 1)
	{
		if (compar(arr + j * size, pivot) < 0)
		{
			i++;
			swap(arr + i * size, arr + j * size, size);
		}
		j++;
	}
	swap(arr + (i + 1) * size, pivot, size);
	return (arr + (i + 1) * size);
}

void	quick_sort(void *base, size_t n_items, size_t size,
					int (*compar)(const void *, const void *))
{
	void	*pivot;
	size_t	index;

	if (n_items < 2)
		return ;
	pivot = partition(base, n_items, size, compar);
	index = (char *)pivot - (char *)base;
	quick_sort(base, (index / size), size, compar);
	quick_sort((char *)pivot + size, n_items - index / size - 1, size, compar);
}
