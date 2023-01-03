/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:40:35 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:14:39 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t const	src_len = ft_strlen(src);
	size_t			cur;

	if (dstsize == 0)
		return (src_len);
	cur = 0;
	while (cur < src_len && cur < dstsize - 1)
	{
		dst[cur] = src[cur];
		cur++;
	}
	dst[cur] = '\0';
	return (src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	s_len;
	size_t	cur;

	if (!s || !f)
		return (0);
	cur = 0;
	s_len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * s_len + 1);
	if (!ret)
		return (0);
	while (cur < s_len)
	{
		ret[cur] = f(cur, s[cur]);
		cur++;
	}
	ret[cur] = 0;
	return (ret);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cur;

	cur = 0;
	while (cur < n)
	{
		if ((s1[cur] == '\0' || s2[cur] == '\0') || s1[cur] != s2[cur])
			return ((unsigned char)s1[cur] - (unsigned char)s2[cur]);
		cur++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	long long	cur_h;
	long long	cur_n;
	long long	len_h;
	long long	len_n;
	int			flag;

	if (!(*needle))
		return ((char *)haystack);
	cur_h = -1;
	len_h = ft_strlen(haystack);
	len_n = ft_strlen(needle);
	while (++cur_h + (size_t)len_n - 1 < len && cur_h + len_n - 1 < len_h)
	{
		cur_n = -1;
		flag = 1;
		while (++cur_n < len_n)
		{
			if (haystack[cur_h + cur_n] != needle[cur_n])
				flag = 0;
		}
		if (flag)
			return ((char *)haystack + cur_h);
	}
	return (0);
}
