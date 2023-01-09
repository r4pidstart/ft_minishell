/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:04:43 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 13:51:32 by joowpark         ###   ########.fr       */
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
	char	*tmpline;
	char	*old;
	char	*new;

	if (*node_line)
	{
		free(*node_line);
		*node_line = NULL;
	}
	new = ft_strdup("");
	lim_l = ft_strlen(limiter);
	while (1)
	{
		ft_fprintf(2,">");
		tmpline = get_next_line(0); //readline(">");
		tmpline[ft_strlen(tmpline) - 1] = '\0';
		if (ft_strncmp(limiter, tmpline, lim_l + 1) == 0)
				break ;
		tmpline[ft_strlen(tmpline)] = '\n';
		old = new;
		new = ft_strjoin(old, tmpline);
		free(old);
		free(tmpline);
	}
	*node_line = new;
	return (0);
}

/*
static void	__here_doc(int *fd, char *limiter)
{
	char	*str;

	close(fd[0]);
	//dup2(fd[1], 1);
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strncmp(str, limiter, ft_strlen(limiter) + 1) == 0)
				break ;
		ft_fprintf(fd[1], "%s\n",str);
		free(str);
	}
	close(fd[1]);
	exit(0);
}

static int __redirection_heredoc(char *limiter)
{
	pid_t	pid;
	int		fd[2];
	int		stat;

	pipe(fd);
	pid = fork();
	stat = 0;
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], 0);
		waitpid(pid, &stat, WNOHANG);
		close(fd[0]);
	}
	else
		__here_doc(fd, limiter);
	return (stat);
}
*/
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
