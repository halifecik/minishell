#include "string_utils.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	const unsigned char	*src_ptr;
	unsigned char		*dst_ptr;

	if (!dst && !src)
		return (0);
	src_ptr = (const unsigned char *)src;
	dst_ptr = (unsigned char *)dst;
	while (len-- > 0)
		*dst_ptr++ = *src_ptr++;
	return (dst);
}

char	*ft_strcat(char *dst, const char *src)
{
	char	*original_dst;
	size_t	len;

	original_dst = dst;
	while (*dst)
		dst++;
	len = ft_strlen(src);
	while (*src && len > 0)
	{
		*dst++ = *src++;
		len--;
	}
	*dst = '\0';
	return (original_dst);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*original_dst;

	original_dst = dst;
	while (src && *src && n > 0)
	{
		*dst++ = *src++;
		n--;
	}
	*dst = '\0';
	while (n > 0)
	{
		*dst++ = '\0';
		n--;
	}
	return (original_dst);
}
