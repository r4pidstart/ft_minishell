/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:10:54 by tjo               #+#    #+#             */
/*   Updated: 2022/12/29 17:45:27 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static size_t	find_next(char **s)
{
	size_t	idx;

	idx = 0;
	while ((*s)[idx] != '/' && (*s)[idx] != '\0')
		idx++;
	return (idx);
}

static int	home_option(char **s)
{
	size_t	idx;
	int		chk;
	char	*path[2];

	(*s)++;
	if (*s[0] == '/' || *s[0] == '\0')
		path[1] = get_env("HOME");
	else
	{
		idx = find_next(s);
		path[0] = ft_substr(*s, 0, idx);
		path[1] = ft_strjoin("/Users/", path[0]);
		if (!path[0] || !path[1])
			return (1);
		free(path[0]);
	}
	chk = chdir(path[1]);
	free(path[1]);
	if (!chk && (*s[0] == '/' || *s[0] == '\0'))
		(*s) += (*s[0] == '/');
	else if (!chk)
		(*s) += idx + 1;
	return (chk);
}

static int	option_check(char **s)
{
	int	cnt;

	if (((*s)[0] == '~' || (*s)[0] == '\0') && home_option(s))
		return (1);
	while ((*s)[0] == '.')
	{
		cnt = 0;
		while ((*s)[1] == '.')
		{
			cnt++;
			(*s)++;
		}
		(*s) += 1 + ((*s)[1] == '/');
		while (cnt-- > 0)
			chdir("..");
	}
	return (0);
}

int	cd(char **s)
{
	static char	*prev_path;
	char		*now_path;
	char		*path;

	path = s[1];
	if (s[1] && s[2] != 0)
		return (error_handling("cd", "too many arguments", 0));
	if (!s[1])
		path = dummy_string();
	if (prev_path == 0)
		prev_path = getcwd(NULL, 0);
	now_path = getcwd(NULL, 0);
	if (path[0] == '-' && path[1] == '\0')
		path = prev_path;
	if (!(!now_path || option_check(&path)) \
		&& path && path[0] != '\0' && chdir(path))
		return (free(now_path), error_handling("cd", 0, path));
	if (path == prev_path)
		pwd(NULL);
	if (!s[1])
		free(path - 1);
	free(prev_path);
	prev_path = now_path;
	return (0);
}
