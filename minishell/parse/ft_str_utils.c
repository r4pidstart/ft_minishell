/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:11:46 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/28 15:25:56 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"

char	*ft_strstrim(char *line)
{
	char	*start;
	char	*end;

	start = line;
	end = line + ft_strlen(line) - 1;
	while (*start && ft_isspace(*start))
	{
		*start = '\0';
		start += 1;
	}
	while (*end && ft_isspace(*end))
	{
		*end = 0;
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
