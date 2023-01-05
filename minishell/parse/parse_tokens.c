/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 09:06:48 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 13:52:11 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_error_tokens(char **tokens, size_t idx)
{
	if (idx == 0)
		idx += 1;
	error_handling(MINISHELL, "syntax error near unexpected token",
		tokens[idx - 1]);
	return (1);
}

static int	check_tokens(char **tokens)
{
	size_t	idx;

	idx = 0;
	while (tokens[idx])
	{
		if (idx % 2 == 0)
		{
			if (ft_strncmp(tokens[idx], "&&", 3) == 0
				|| ft_strncmp(tokens[idx], "||", 3) == 0)
				break ;
			if (ft_strlen(tokens[idx]) == 0)
			{
				error_handling(MINISHELL, "syntax error near unexpected token",
					tokens[idx - 1]);
				return (1);
			}
		}
		idx += 1;
	}
	if (!(idx % 2))
		return (print_error_tokens(tokens, idx));
	return (0);
}

static void	__parse_tokens(char **ret, char *cmd, int nr_tokens)
{
	char	*line;
	int		is_gal;

	is_gal = 0;
	line = cmd;
	while (*cmd)
	{
		if (is_gal == 0 && (*cmd == '\'' || *cmd == '\"'))
			is_gal = *cmd;
		else if (is_gal == 0 && (ft_strncmp(cmd, "&&", 2) == 0
				|| ft_strncmp(cmd, "||", 2) == 0))
		{
			if (cmd != line)
				ret[nr_tokens++] = ft_strndup(line, cmd - line);
			ret[nr_tokens++] = ft_strndup(cmd, 2);
			line = cmd + 2;
			cmd += 1;
		}
		else if (is_gal == *cmd)
			is_gal = 0;
		cmd += 1;
	}
	if (cmd != line)
		ret[nr_tokens ++] = ft_strndup(line, cmd - line);
	ret[nr_tokens] = NULL;
}

char	**parse_tokens(char *line)
{
	char	**ret;
	int		nr_tokens;

	ret = malloc(sizeof(*ret) * ft_strlen(line));
	if (!ret)
		return (ret);
	nr_tokens = 0;
	__parse_tokens(ret, ft_strstrim(line), nr_tokens);
	if (check_tokens(ret))
	{
		free_tokens(ret);
		return (NULL);
	}
	return (ret);
}
