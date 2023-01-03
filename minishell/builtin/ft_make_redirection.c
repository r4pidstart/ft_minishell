/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:04:43 by tjo               #+#    #+#             */
/*   Updated: 2023/01/03 15:01:34 by joowpark         ###   ########.fr       */
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
	return (ret);
}

static int	__redirection_input(char *target, int type)	//JOOWPARK
{
	int	new_fd;
	int	ret;

	new_fd = open(target, O_RDONLY | O_CREAT * type, 0644);
	if (new_fd < 0)
		return (1);
	ret = dup2(new_fd, STDIN_FILENO);
	close(new_fd);
	return (ret);
}

static int	__redirection_heredoc(char *limiter)
{
	int		fd;
	int		lim_l;
	char	*tmpline;

	fd = open(get_heredoc_path(), O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd < 0)
		return (1);
	ft_fprintf(2, "> ");
	tmpline = get_next_line(0);
	if (!tmpline)
		return (1);
	lim_l = ft_strlen(limiter);
	while (ft_strncmp(limiter, tmpline, lim_l) || tmpline[lim_l] != '\n')
	{
		ft_fprintf(fd, "%s", tmpline);
		ft_fprintf(2, "> ");
		free(tmpline);
		tmpline = get_next_line(0);
		if (!tmpline)
			return (1);
	}
	close(fd);
	__redirection_input(get_heredoc_path(), 1);
	return (0);
}

static int	__redirection(char *target, int type)
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
	else if (type == R_HERE_DOC)
		ret = __redirection_heredoc(trimmed_target);
	else
		ret = 1;
	if (type == R_INPUT && ret) // JOOWPARK
		return (error_handling("minishell: ","no such file or directory: ", trimmed_target));
	free(trimmed_target);
	free(target);
	return (ret);
}

int	make_redirection(char **s)
{
	int		type;
	int		idx;
	char	*target;

	idx = 0;
	type = 0;
	while (s[0][idx])
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
		idx++;
	}
	if (s[0][idx] == '\0' && s[1] == NULL)
		return (1);
	if (s[0][idx] == '\0')
		target = ft_strdup(s[1]);
	else
		target = ft_substr(s[0], idx, -1);
	return (__redirection(target, type));
}
