/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:37:31 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:14:24 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s + i) == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (0);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((unsigned char *)s1 + i) != *((unsigned char *)s2 + i))
			return (*((unsigned char *)s1 + i) - *((unsigned char *)s2 + i));
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cur;

	if (dst == src)
		return (dst);
	cur = -1;
	while (++cur < n)
		*(char *)(dst + cur) = *((char *)src + (cur));
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	cur;

	if (dst == src)
		return (dst);
	if (dst < src)
	{
		cur = 0;
		while (0 <= cur && cur < len)
		{
			*((char *)dst + cur) = *((char *)src + cur);
			cur++;
		}
	}
	else
	{
		cur = len - 1;
		while (0 <= cur && cur < len)
		{
			*((char *)dst + cur) = *((char *)src + cur);
			cur--;
		}
	}
	return (dst);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*cur;

	cur = (char *)b;
	while (len--)
		*(cur++) = (char)c;
	return (b);
}
