/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:46:28 by tjo               #+#    #+#             */
/*   Updated: 2022/12/28 16:19:17 by tjo              ###   ########.fr       */
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

	env_fd = open(ENV_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (s[ft_strlen(target)] == '\0')
		ft_fprintf(env_fd, "%s=''\n", target);
	else
		ft_fprintf(env_fd, "%s\n", s);
	close(env_fd);
	return (0);
}

int	export(char **s)
{
	int		ret;
	char	*exec_str;
	char	*target;

	if (s[1] == 0)
		return (print_all_env());
	s++;
	while (*s)
	{
		target = make_target(*s);
		exec_str = ft_strjoin("unset ", target);
		ret = builtin_executer(exec_str, &unset); // would be modified
		append_new(*s, target);
		free(target);
		free(exec_str);
		s++;
	}
	if (ret != 1)
		return (ret);
	return (0);
}
