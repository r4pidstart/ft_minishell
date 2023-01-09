/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:04:43 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 18:56:39 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

static int	__redirection_output(char *target, int append)
{
	int	new_fd;
	int	ret;

	new_fd = open(target, O_WRONLY | O_APPEND \
		| !append * O_TRUNC | O_CREAT, 0644);
	ret = dup2(new_fd, STDOUT_FILENO);
	close(new_fd);
	return (ret == -1);
}

static int	__redirection_input(char *target, int type)
{
	int	new_fd;
	int	ret;

	new_fd = open(target, O_RDONLY | O_CREAT * type, 0644);
	if (new_fd < 0)
		return (1);
	ret = dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (ret == -1);
}

static int	__redirection_heredoc(char *limiter, char **node_line)
{
	int		lim_l;
	char	*tmp[3];

	if (*node_line)
	{
		free(*node_line);
		*node_line = NULL;
	}
	tmp[2] = ft_strdup("");
	lim_l = ft_strlen(limiter);
	while (1)
	{
		ft_fprintf(1, ">");
		tmp[0] = get_next_line(0);
		tmp[0][ft_strlen(tmp[0]) - 1] = '\0';
		if (ft_strncmp(limiter, tmp[0], lim_l + 1) == 0)
			break ;
		tmp[0][ft_strlen(tmp[0])] = '\n';
		tmp[1] = tmp[2];
		tmp[2] = ft_strjoin(tmp[1], tmp[0]);
		free(tmp[1]);
		free(tmp[0]);
	}
	*node_line = tmp[2];
	return (0);
}

static int	__redirection(char *target, int type, char **node_line, int here)
{
	int		ret;
	char	*trimmed_target;

	trimmed_target = ft_strtrim(target, " \n\r\t");
	if (!trimmed_target || !target)
		return (1);
	if (type == R_OUTPUT || type == R_APPEND)
		ret = __redirection_output(trimmed_target, type == R_APPEND);
	else if (type == R_INPUT)
		ret = __redirection_input(trimmed_target, 0);
	else if (type == R_HERE_DOC && here)
		ret = __redirection_heredoc(trimmed_target, node_line);
	else if (type == R_HERE_DOC && !here)
		ret = 0;
	else
		ret = 1;
	if (type == R_INPUT && ret)
	{
		redirect_status(1);
		ret = error_handling("minishell", trimmed_target \
			, "no such file or directory");
	}
	free(trimmed_target);
	free(target);
	return (ret);
}

int	make_redirection(char **s, char **node_line, int here)
{
	int		type;
	int		idx;

	idx = -1;
	type = 0;
	while (s[0][++idx])
	{
		if (s[0][idx] == '<' && type == R_NORMAL)
			type = R_INPUT;
		else if (s[0][idx] == '<' && type == R_INPUT)
			type = R_HERE_DOC;
		else if (s[0][idx] == '>' && type == NORMAL)
			type = R_OUTPUT;
		else if (s[0][idx] == '>' && type == R_OUTPUT)
			type = R_APPEND;
		else if (!ft_isspace(s[0][idx]) || !s[0][idx])
			break ;
	}
	if (s[0][idx] == '\0' && s[1] == NULL)
		return (redirect_status(1) * -42);
	if (s[0][idx] == '\0')
		return (__redirection(ft_strdup(s[1]), type, node_line, here));
	else
		return (__redirection(ft_substr(s[0], idx, -1), type, node_line, here));
}
