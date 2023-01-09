/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_executer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:27:08 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 18:23:34 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	ft_pre_executer(char *s, struct s_node *node)
{
	char	**parsed;
	int		ret;

	ret = 0;
	if (redirect_status(2))
		return (1);
	parsed = quote_parser(s);
	wildcard_parser(&parsed);
	if (*parsed && (parsed[0][0] == '<' || parsed[0][0] == '>'))
	{
		ret = check_redirect(parsed, node, 1);
	}
	exit_code_export(ret);
	if (ret == 1 && (*parsed[0] == '<' || *parsed[0] == '>'))
		ret = -42;
	free_parsed(parsed);
	if (ret == -42)
		return (error_handling("minishell: ", \
			"syntax error near unexpected token ", "\\n"));
	return (ret);
}
