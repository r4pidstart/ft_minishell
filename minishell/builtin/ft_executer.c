/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:52:15 by tjo               #+#    #+#             */
/*   Updated: 2023/01/10 01:17:49 by tjo              ###   ########.fr       */
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

int	exit_code_export(int ret)
{
	char	**tmp;
	char	*tmpret;

	g_exit_code = ret;
	tmp = (char **)malloc(sizeof(char *) * 3);
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

int	exec(char **parsed, struct s_node *node, int is_in_pipe)
{
	int	ret;
	int	(*func)(char **);

	select_builtin_func(parsed[0], &func);
	get_input_line(node, is_in_pipe);
	if (func)
	{
		if (is_in_pipe && (func == &export || func == &unset))
			exit(0);
		ret = func(parsed);
		if (is_in_pipe)
			exit(0);
	}
	else
	{
		if (parsed[0][0] == '\0')
			return (error_handling("minishell", \
				parsed[0], "command not found"), 127);
		if (!is_in_pipe)
			ret = fork_execve(parsed);
		else
			ret = non_fork_execve(parsed);
	}
	return (ret);
}

int	free_parsed(char **parsed)
{
	char	**ptr;

	ptr = parsed;
	while (*ptr)
		free(*(ptr++));
	free(parsed);
	return (0);
}

int	builtin_executer(struct s_node *node, char *s, int is_in_pipe)
{
	char	**parsed;
	int		ret;

	ret = 0;
	if (redirect_status(2))
		return (1);
	parsed = quote_parser(s);
	wildcard_parser(&parsed);
	if (*parsed && (parsed[0][0] == '<' || parsed[0][0] == '>'))
		ret = check_redirect(parsed, node, 0);
	else if (node->type == PIPE)
		ret = make_pipe(node);
	else if (*parsed)
		ret = exec(parsed, node, is_in_pipe);
	if (!(ft_strlen(s) == 1 && s[0] == '|'))
		exit_code_export(ret);
	if (ret == 1 && (*parsed[0] == '<' || *parsed[0] == '>'))
		ret = -42;
	free_parsed(parsed);
	if (ret == -42)
		return (redirect_status(1), error_handling("minishell: ", \
			"syntax error near unexpected token ", "\\n"));
	return (ret);
}
