/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 03:41:35 by tjo               #+#    #+#             */
/*   Updated: 2022/08/30 04:14:43 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"./ft_libft.h"

static size_t	__min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	substr_len = __min(len, ft_strlen(s + start));
	ret = (char *)malloc(sizeof(char) * substr_len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s + start, substr_len);
	ret[substr_len] = 0;
	return (ret);
}

static int	char_check(const char c, char *set)
{
	set--;
	while (*(++set) != '\0')
		if (c == *set)
			return (1);
	return (0);
}

static void	get_cur(size_t *lcur, size_t *rcur, char const *s1, char const *set)
{
	size_t	s_len;

	s_len = ft_strlen(s1);
	*lcur = 0;
	*rcur = s_len - 1;
	while (1)
	{
		if (!(*lcur < *rcur))
		{
			if (char_check(s1[*lcur], (char *)set))
				(*lcur)++;
			return ;
		}
		else if (*lcur < s_len && char_check(s1[*lcur], (char *)set))
			(*lcur)++;
		else if (0 <= *rcur && char_check(s1[*rcur], (char *)set))
			(*rcur)--;
		else
			return ;
	}
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	size_t	ret_len;
	size_t	lcur;
	size_t	rcur;

	if (!s1 || !set)
		return (0);
	get_cur(&lcur, &rcur, s1, set);
	ret_len = rcur - lcur + 1;
	ret = (char *)malloc(sizeof(char) * ret_len + 1);
	if (!ret)
		return (0);
	ft_memmove(ret, s1 + lcur, ret_len);
	ret[ret_len] = '\0';
	return (ret);
}
