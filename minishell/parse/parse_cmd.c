/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:09:42 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 10:18:39 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*get_file_name(char *cmd, char **line)
{
	char	*ret;

	while (ft_isspace(*cmd))
		cmd ++;
	while (!ft_isspace(*cmd) && *cmd != '<'
		&& *cmd != '|' && *cmd != '>' && *cmd)
		cmd ++;
	ret = ft_strndup(*line, cmd - *line);
	*line = cmd;
	return (ret);
}

static char	*get_redir_pipe(char **line)
{
	char	*cmd;
	char	*ret;

	cmd = *line;
	if (ft_strlen(cmd) > 2 && (ft_strncmp(cmd, "<<", 2) == 0
			|| ft_strncmp(cmd, ">>", 2) == 0))
		cmd += 2;
	else if (*cmd == '<')
		cmd += 1;
	else if (*cmd == '>')
		cmd += 1;
	else if (*cmd == '|')
	{
		*line += 1;
		return (ft_strdup("|"));
	}
	else
		return (NULL);
	ret = ft_strstrim(get_file_name(cmd, line));
	return (ret);
}

static void	cmgxg(int *is_gal, char *cmd)
{
	if (*is_gal == 0)
		*is_gal = *cmd;
	else if (*cmd == *is_gal)
		*is_gal = 0;
}

char	*get_cmd(char **line)
{
	char	*cmd;
	char	*ret;
	int		is_gal;

	is_gal = 0;
	cmd = *line;
	ret = get_redir_pipe(line);
	if (ret)
		return (ft_strstrim(ret));
	while (*cmd)
	{
		if (*cmd == '\'' || *cmd == '\"')
		{
			if (*cmd == is_gal || is_gal == 0)
				cmgxg(&is_gal, cmd);
		}
		if (is_gal == 0 && ft_strchr(DELTOKEN, *cmd))
			break ;
		cmd += 1;
	}
	ret = ft_strndup(*line, cmd - *line);
	if (!ret)
		return (ret);
	*line = cmd;
	return (ft_strstrim(ret));
}

int	parse_cmd(char **tokens, char *cmd, int *nr_tokens)
{
	char	*line;

	line = cmd;
	*nr_tokens = 0;
	line = ft_strstrim(line);
	while (*line)
	{
		tokens[*nr_tokens] = get_cmd(&line);
		*nr_tokens += 1;
		line = ft_strstrim(line);
	}
	tokens[*nr_tokens] = NULL;
	if (check_pipe(tokens))
	{
		write(2, "minishell: parse error near `|'\n", 32);
		return (1);
	}
	return (*nr_tokens < 0);
}
