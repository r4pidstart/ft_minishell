/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:11:46 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 23:14:47 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*ft_strstrim(char *line)
{
	char	*start;
	char	*end;

	start = line;
	if (!ft_strlen(line))
		return (start);
	end = line + ft_strlen(line) - 1;
	while (*start && ft_isspace(*start))
	{
		start += 1;
	}
	while (*end && ft_isspace(*end))
	{
		*end = '\0';
		end -= 1;
	}
	return (start);
}

char	*ft_strndup(char *line, size_t pos)
{
	char	*ret;

	ret = malloc(sizeof(char) * (pos + 1));
	if (!ret)
		return (ret);
	ft_strlcpy(ret, line, pos + 1);
	return (ret);
}
