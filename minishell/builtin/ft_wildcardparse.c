/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcardparse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:05:57 by tjo               #+#    #+#             */
/*   Updated: 2023/01/04 15:13:03 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	check_wildcard(char *str, int *ret)
{
	int		quote;
	size_t	idx;

	quote = 0;
	idx = -1;
	while (str[++idx])
	{
		if (!quote && str[idx] == '*')
		{
			*ret = idx;
			return (1);
		}
		else if (!quote && str[idx] == '\'')
			quote = SINGLE;
		else if (!quote && str[idx] == '"')
			quote = DOUBLE;
		else if (quote == SINGLE && str[idx] == '\'')
			quote = 0;
		else if (quote == DOUBLE && str[idx] == '"')
			quote = 0;
	}
	return (0);
}

static int	check_pattern(int idx, char *str, char *target)
{
	if (target + ft_strlen(target) - (ft_strlen(str) - idx) + 1 < target)
		return (0);
	if (ft_strncmp(str, target, idx))
		return (0);
	if (ft_strncmp(str + idx + 1, \
		target + ft_strlen(target) - (ft_strlen(str) - idx) + 1, -1))
		return (0);
	target[ft_strlen(target)] = 7;
	target[ft_strlen(target) + 1] = '\0';
	return (1);
}

static char	*replace_wildcard(int idx, char *str)
{
	DIR				*dir;
	struct dirent	*info;
	char			*ret[2];

	dir = opendir(".");
	info = readdir(dir);
	ret[0] = dummy_string();
	while (info)
	{
		if (info->d_name[0] != '.' && check_pattern(idx, str, info->d_name))
		{
			ret[1] = ft_strjoin(ret[0], info->d_name);
			free(ret[0]);
			ret[0] = ret[1];
		}
		info = readdir(dir);
	}
	closedir(dir);
	if (ft_strlen(ret[0]))
	{
		ret[0][ft_strlen(ret[0]) - 1] = '\0';
		return (free(str), ret[0]);
	}
	return (str);
}

int	wildcard_parser(char ***parsed)
{
	char	**cur;
	int		ret;
	int		idx;

	cur = *parsed;
	while (*cur)
	{
		ret = check_wildcard(*cur, &idx);
		if (ret)
			*cur = replace_wildcard(idx, *cur);
		cur++;
	}
	reorder_parsed(parsed);
	return (0);
}
