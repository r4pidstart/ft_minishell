/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:46:28 by tjo               #+#    #+#             */
/*   Updated: 2023/01/10 00:44:16 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static char	*make_target(char *s)
{
	int	idx;

	idx = 0;
	while (s[idx] != '\0' && s[idx] != '=')
		idx++;
	return (ft_substr(s, 0, idx));
}

static int	append_new(char *s, char *target)
{
	int	env_fd;

	env_fd = open(get_env_path(), O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (s[ft_strlen(target)] == '\0')
		ft_fprintf(env_fd, "%s=''\n", target);
	else
		ft_fprintf(env_fd, "%s\n", s);
	close(env_fd);
	return (0);
}

static int	unset_target(char *target)
{
	char	**tmp;

	tmp = (char **)malloc(sizeof(char **) * 3);
	if (!tmp)
		return (1);
	tmp[0] = "export";
	tmp[1] = target;
	tmp[2] = 0;
	unset(tmp);
	free(tmp);
	return (0);
}

int	export(char **s)
{
	int		ret;
	char	*target;

	if (s[1] == 0)
		return (print_all_env());
	s++;
	while (*s)
	{
		target = make_target(*s);
		ret = unset_target(target);
		append_new(*s, target);
		free(target);
		s++;
	}
	if (ret != 0)
		return (error_handling("export", 0, 0));
	return (0);
}
