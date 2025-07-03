/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:48:44 by hademirc          #+#    #+#             */
/*   Updated: 2025/07/03 16:48:45 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# define STRING_UTILS_H

# include <stddef.h>

typedef unsigned char	t_uint8;

typedef struct s_list
{
	char			*value;
	struct s_list	*next;
}		t_list;

//node_functions.c
void			node_destroy_list(t_list **head);
char			node_create(t_list **head, char *value);
char			node_insert(t_list **head, char *str, size_t len);
void			node_destroy_empty(t_list **head);

//string_utils_char_check.c
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_tolower(int c);

//string_utils_search.c
size_t			ft_strlen(const char *s);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

//string_utils_copy.c
void			*ft_memcpy(void *dst, const void *src, size_t len);
char			*ft_strcat(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);

//string_utils_malloc.c
char			*ft_strdup(const char *s);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strmjoin(char *s1, const char *s2);

//string_utils_quick_sort.c
void			quick_sort(void *base, size_t n_items, size_t size,
					int (*compar)(const void *, const void *));

//string_utils_strtok.c
char			*ft_strtok(char *str, const char *delim);

//string_utils_type_conversions.c
char			*ft_ltoa(long n);
unsigned char	ft_atouc(char *str);
char			**list_to_array(t_list **head);

//string_utils_atol.c
long			ft_atol(const char *str, unsigned char (*error_case)(void));

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//string_utils_gnl.c
char			*get_next_line(int fd);

#endif
