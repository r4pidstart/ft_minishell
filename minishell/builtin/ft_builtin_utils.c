/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:16:34 by tjo               #+#    #+#             */
/*   Updated: 2022/12/26 19:16:45 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	ft_isalnum(int c)
{
	return (('0' <= c && c <= '9') \
	|| ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

char	*string_concatnation(char *str, t_ex_env *t, int env)
{
	char	*tmp;
	char	*env_tmp;
	char	*ret;

	tmp = ft_substr(str + t->e, 0, t->s - t->e);
	if (!tmp)
		return (0);
	if (env)
	{
		env_tmp = get_env(tmp);
		free(tmp);
		tmp = env_tmp;
	}
	ret = ft_strjoin(t->ret, tmp);
	free(t->ret);
	return (ret);
}

char	*expend_env(char *s)
{
	t_ex_env	st;

	st = (t_ex_env){.ret = dummy_string(), .s = 0, .e = 0, .status = 0};
	while (s[st.s])
	{
		if (st.status == ENV_START && s[st.s] == '{')
			st.e++;
		else if (st.status == ENV_START && (!ft_isalnum(s[st.s])))
		{
			st.status = NORMAL;
			st.ret = string_concatnation(s, &st, 1);
			st.e = st.s + (s[st.s] == '}');
			if (s[st.s] == '$')
				st.s--;
		}
		else if (st.status == NORMAL && s[st.s] == '$')
		{
			st.status = ENV_START;
			st.ret = string_concatnation(s, &st, 0);
			st.e = st.s + 1;
		}
		st.s++;
	}
	if (st.status == ENV_START)
		st.ret = string_concatnation(s, &st, 1);
	else
		st.ret = string_concatnation(s, &st, 0);
	return (st.ret);
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
	st.env_fd = open(ENV_FILE, O_CREAT | O_RDONLY, 0644);
	st.target = ft_strjoin(target, "=");
	while (1)
	{
		st.tmp = get_next_line(st.env_fd);
		if (!st.tmp)
			break ;
		if (!ft_strncmp(st.tmp, st.target, ft_strlen(st.target)))
			st.env = ft_strdup(st.tmp);
		free(st.tmp);
	}
	if (!st.env)
		st.ret = dummy_string();
	else
		st.ret = ft_strdup(st.env + ft_strlen(st.target) + 1);
	free(st.env);
	close(st.env_fd);
	if (st.env && st.ret[ft_strlen(st.ret) - 1] == '\n')
		st.ret[ft_strlen(st.ret) - 1] = '\0';
	return (st.ret);
}
