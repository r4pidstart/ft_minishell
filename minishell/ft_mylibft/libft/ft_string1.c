/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:39:31 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:14:33 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	target_len;
	char	*ret;

	target_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * target_len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s1, target_len);
	ret[target_len] = '\0';
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	char			*cur;
	unsigned char	target;

	cur = (char *)s - 1;
	target = (unsigned char)c;
	while (cur++)
	{
		if (*cur == target)
			return (cur);
		if (*cur == '\0')
		{
			if (c == '\0')
				return (cur);
			else
				return (0);
		}
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * s1_len + s2_len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s1, s1_len);
	ft_memmove(ret + s1_len, s2, s2_len);
	ret[s1_len + s2_len] = 0;
	return (ret);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	cur;

	src_len = ft_strlen(src);
	dst_len = 0;
	while (dst[dst_len])
	{
		if (dstsize < dst_len)
			return (dstsize + src_len);
		dst_len++;
	}
	if (dstsize < dst_len)
		return (dstsize + src_len);
	cur = dst_len;
	while (cur - dst_len < src_len && cur + 1 < dstsize)
	{
		dst[cur] = src[cur - dst_len];
		cur++;
	}
	dst[cur] = '\0';
	return (dst_len + src_len);
}
