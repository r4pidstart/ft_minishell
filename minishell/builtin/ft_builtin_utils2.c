/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 19:45:45 by tjo               #+#    #+#             */
/*   Updated: 2022/12/27 16:58:40 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

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
	st.env_fd = open(ENV_FILE, O_CREAT | O_RDONLY, 0644);
	while (1)
	{
		st.tmp = get_next_line(st.env_fd);
		if (!st.tmp)
			break ;
		if (!ft_strncmp(st.tmp, st.target, ft_strlen(st.target)))
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

	env_fd = open(ENV_FILE, O_CREAT | O_RDONLY, 0644);
	while (1)
	{
		env = get_next_line(env_fd);
		if (!env)
			return (1);
		ft_printf("%s", env);
		free(env);
	}
	close(env_fd);
}

int	quote_parser(char *s)
{
	
}