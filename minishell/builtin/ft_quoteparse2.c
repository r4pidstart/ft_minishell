/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quoteparse2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 17:05:53 by tjo               #+#    #+#             */
/*   Updated: 2023/01/04 12:56:41 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static char	*processing_concat(char *s, t_parser *st, int env)
{
	char	*tmp;
	char	*env_tmp;
	char	*ret;

	if (env == 2)
	{
		st->e--;
		st->s++;
	}
	tmp = ft_substr(s + st->e, 0, st->s - st->e);
	if (env == 1)
	{
		env_tmp = expend_env(tmp);
		free(tmp);
		tmp = env_tmp;
	}
	ret = ft_strjoin(st->ret, tmp);
	free(st->ret);
	free(tmp);
	st->e = st->s + 1 - (env == 2);
	st->status = NORMAL;
	return (ret);
}

static char	*processing(char *s)
{
	t_parser	st;

	st = (t_parser){.ret = dummy_string(), .s = 0, .e = 0, .status = 0};
	while (s[st.s])
	{
		if (ft_isspace(s[st.s]) && (st.status == SINGLE || st.status == DOUBLE))
			s[st.s] = 7;
		else if (ft_isspace(s[st.s]))
			s[st.s] = 32;
		if (st.status == SINGLE && s[st.s] == '\'')
			st.ret = processing_concat(s, &st, 0);
		else if (st.status == DOUBLE && s[st.s] == '"')
			st.ret = processing_concat(s, &st, 1);
		else if (st.status == NORMAL && (s[st.s] == '\'' || s[st.s] == '"'))
		{
			st.ret = processing_concat(s, &st, 1);
			st.status = DOUBLE;
			if (s[st.s] == '\'')
				st.status = SINGLE;
		}
		st.s++;
	}
	st.ret = processing_concat(s, &st, 1);
	return (st.ret);
}

// 1. change whitespace to -1 and 7(bell) and expend the env
// 2. split
// 3. restore bell to space
char	**quote_parser(char *str)
{
	char		*s;
	char		**splited;
	char		**pstring;
	char		*pchar;

	s = processing(str);
	splited = ft_split(s, ' ');
	free(s);
	pstring = splited;
	while (*pstring)
	{
		pchar = *pstring;
		while (*pchar)
		{
			if (*pchar == 7)
				*pchar = ' ';
			pchar++;
		}
		pstring++;
	}
	return (splited);
}

// process without single quotes
static char	*preprocessing(char *s)
{
	t_parser	st;

	st = (t_parser){.ret = dummy_string(), .s = 0, .e = 0, .status = 0};
	while (s[st.s])
	{
		if (ft_isspace(s[st.s]) && st.status == DOUBLE)
			s[st.s] = 7;
		else if (ft_isspace(s[st.s]))
			s[st.s] = 32;
		if (st.status == DOUBLE && s[st.s] == '\'')
			st.ret = processing_concat(s, &st, 2);
		else if (st.status == NORMAL && s[st.s] == '\'')
		{
			st.ret = processing_concat(s, &st, 1);
			st.status = DOUBLE;
		}
		st.s++;
	}
	st.ret = processing_concat(s, &st, 1);
	return (st.ret);
}

char	*line_env_expender(char *str)
{
	return (preprocessing(str));
}
