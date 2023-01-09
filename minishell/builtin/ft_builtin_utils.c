/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:45:45 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 23:28:52 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

char	*get_heredoc_path(void)
{
	static char	*path;

	if (!path)
		path = ft_strjoin(getenv("HOME"), "/.heredoc_tmp");
	return (path);
}

char	*dummy_string(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * 1);
	if (!ret)
		return (0);
	ret[0] = 0;
	return (ret);
}

char	*get_env(char *target)
{
	t_get_env	st;

	st.env = 0;
	st.target = ft_strjoin(target, "=");
	st.env_fd = open(get_env_path(), O_CREAT | O_RDWR, 0644);
	while (1)
	{
		st.tmp = get_next_line(st.env_fd);
		if (!st.tmp)
			break ;
		if (!st.env && !ft_strncmp(st.tmp, st.target, ft_strlen(st.target)))
			st.env = ft_strdup(st.tmp);
		free(st.tmp);
	}
	close(st.env_fd);
	if (!st.env)
		st.ret = dummy_string();
	else
		st.ret = ft_strdup(st.env + ft_strlen(st.target));
	if (st.env && st.ret[ft_strlen(st.ret) - 1] == '\n')
		st.ret[ft_strlen(st.ret) - 1] = '\0';
	free(st.env);
	free(st.target);
	return (st.ret);
}

int	print_all_env(void)
{
	int		env_fd;
	char	*env;

	env_fd = open(get_env_path(), O_CREAT | O_RDONLY, 0644);
	while (1)
	{
		env = get_next_line(env_fd);
		if (!env)
			return (1);
		ft_printf("declare -x %s", env);
		free(env);
	}
	close(env_fd);
}

int	redirect_status(int cmd)
{
	static int	stat;

	if (cmd == 0)
		stat = 0;
	if (cmd == 1)
		stat = 1;
	return (stat);
}
