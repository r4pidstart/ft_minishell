/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:52:15 by tjo               #+#    #+#             */
/*   Updated: 2023/01/03 15:02:06 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static void	select_builtin_func(char *s, int (**func)(char **))
{
	if (ft_strncmp(s, "echo", 5) == 0)
		*func = &echo;
	else if (ft_strncmp(s, "cd", 3) == 0)
		*func = &cd;
	else if (ft_strncmp(s, "pwd", 4) == 0)
		*func = &pwd;
	else if (ft_strncmp(s, "export", 7) == 0)
		*func = &export;
	else if (ft_strncmp(s, "unset", 6) == 0)
		*func = &unset;
	else if (ft_strncmp(s, "env", 4) == 0)
		*func = &env;
	else if (ft_strncmp(s, "exit", 5) == 0)
		*func = &ft_exit;
	else
		*func = NULL;
}

static int	exit_code_export(int ret)
{
	char	**tmp;
	char	*tmpret;

	tmp = (char **)malloc(sizeof(char **) * 3);
	tmpret = ft_itoa(ret);
	if (!tmp || !tmpret)
		return (1);
	tmp[0] = "export";
	tmp[1] = ft_strjoin("?=", tmpret);
	tmp[2] = 0;
	if (!tmp[1])
		return (1);
	export(tmp);
	free(tmp[1]);
	free(tmpret);
	free(tmp);
	return (0);
}

int	builtin_executer(struct s_node *node, char *s, int is_in_pipe)
{
	char	**parsed;
	char	**ptr;
	int		ret;
	int		(*func)(char **);

	ret = 0;
	node->type = node->type;
	parsed = quote_parser(s);
	if (parsed[0][0] == '<' || parsed[0][0] == '>')
		ret = make_redirection(parsed);
	else if (node->type == PIPE)
		ret = make_pipe(node);
	else
	{
		select_builtin_func(parsed[0], &func);
		if (func)
		{
			ret = func(parsed);
			if (is_in_pipe)
				exit(ret);
		}
		else
		{
			if (!is_in_pipe)
				ret = fork_execve(parsed);
			else
				ret = non_fork_execve(parsed);
		}
	}
	if (ret && (*parsed[0] == '<' || *parsed[0] == '>'))
		return (error_handling("minishell: ", "syntax error near unexpected token ", "\\n"));
	exit_code_export(ret);
	ptr = parsed;
	while (*ptr)
		free(*(ptr++));
	free(parsed);
	return (ret);
}
