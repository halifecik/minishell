#include "string_utils.h"

#include <stdlib.h>
#include <limits.h>

char	*ft_ltoa(long n)
{
	char	*str;
	long	num;
	size_t	len;

	if (n == 0)
		return (ft_strdup("0"));
	num = n;
	len = 0;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

static long	calculate_number(const char *str, unsigned char (*error_case)(void))
{
	long	result;
	char	digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result < (LONG_MIN + digit) / 10)
			return (error_case());
		result = result * 10 - digit;
		str++;
	}
	if (*str != '\0')
		return (error_case());
	return (result);
}

long	ft_atol(const char *str, unsigned char (*error_case)(void))
{
	long		result;
	char		sign;

	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (error_case());
	result = calculate_number(str, error_case);
	if (sign == 1)
	{
		if (result == LONG_MIN)
			return (error_case());
		result = -result;
	}
	return ((long)result);
}

static size_t	node_length(t_list **head)
{
	t_list	*current;
	size_t	length;

	if (!(*head))
		return (0);
	length = 0;
	current = *head;
	while (current)
	{
		length++;
		current = current->next;
	}
	return (length);
}

char	**list_to_array(t_list **head)
{
	t_list	*current;
	char	**array;
	size_t	node_len;

	if (!(*head))
		return (NULL);
	node_len = node_length(head);
	array = malloc(sizeof(char *) * (node_len + 1));
	if (!array)
		return (NULL);
	current = *head;
	node_len = 0;
	while (current)
	{
		array[node_len] = current->value;
		current = current->next;
		node_len++;
	}
	array[node_len] = NULL;
	return (array);
}
