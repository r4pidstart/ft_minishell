/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:16:34 by tjo               #+#    #+#             */
/*   Updated: 2022/12/26 19:57:46 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	ft_isalnum(int c)
{
	return (('0' <= c && c <= '9') \
	|| ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

static char	*string_concatnation(char *str, t_ex_env *t, int env)
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
