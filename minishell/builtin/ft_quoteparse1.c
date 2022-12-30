/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoteparse1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:05:53 by tjo               #+#    #+#             */
/*   Updated: 2022/12/30 18:21:14 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	ft_isalnum(int c)
{
	return (('0' <= c && c <= '9') \
	|| ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
}

static char	*string_concatnation(char *str, t_parser *st, int env)
{
	char	*tmp;
	char	*env_tmp;
	char	*ret;

	tmp = ft_substr(str + st->e, 0, st->s - st->e);
	if (!tmp)
		return (0);
	if (env)
	{
		env_tmp = get_env(tmp);
		free(tmp);
		tmp = env_tmp;
	}
	ret = ft_strjoin(st->ret, tmp);
	free(st->ret);
	free(tmp);
	return (ret);
}

void	expend_concat(char *s, t_parser *st, int type)
{
	if (type == 0)
	{
		st->status = NORMAL;
		st->ret = string_concatnation(s, st, 1);
		st->e = st->s + (s[st->s] == '}');
		if (s[st->s] == '$')
			st->s--;
	}
	else
	{
		st->status = ENV_START;
		st->ret = string_concatnation(s, st, 0);
		st->e = st->s + 1;
	}
}

char	*expend_env(char *s)
{
	t_parser	st;

	st = (t_parser){.ret = dummy_string(), .s = 0, .e = 0, .status = 0};
	while (s[st.s])
	{
		if (st.status == ENV_START && s[st.s] == '{')
			st.e++;
		else if (st.status == ENV_START && \
			(!ft_isalnum(s[st.s]) && s[st.s] != '?'))
			expend_concat(s, &st, 0);
		else if (st.status == NORMAL && s[st.s] == '$')
			expend_concat(s, &st, 1);
		st.s++;
	}
	if (st.status == ENV_START)
		st.ret = string_concatnation(s, &st, 1);
	else
		st.ret = string_concatnation(s, &st, 0);
	return (st.ret);
}
