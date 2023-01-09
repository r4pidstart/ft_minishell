/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:25:59 by tjo               #+#    #+#             */
/*   Updated: 2022/08/31 04:50:18 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

static void	*ft_memmove(void *dst, const void *src, size_t len)
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

static size_t	ft_strlen(const char *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

char	*ft_custom_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	substr_len;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) <= start)
	{
		ret = (char *)malloc(sizeof(char) * 1);
		if (!ret)
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	substr_len = ft_strlen(s + start);
	if (substr_len > len)
		substr_len = len;
	ret = (char *)malloc(sizeof(char) * substr_len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s + start, substr_len);
	ret[substr_len] = 0;
	return (ret);
}

char	*ft_custom_strjoin(char *s1, char *buf, int rd_siz)
{
	char	*ret;
	size_t	s1_len;

	if (!s1 || !buf)
		return (0);
	s1_len = ft_strlen(s1);
	ret = (char *)malloc(sizeof(char) * s1_len + rd_siz + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s1, s1_len);
	ft_memmove(ret + s1_len, buf, rd_siz);
	ret[s1_len + rd_siz] = 0;
	free(s1);
	return (ret);
}
