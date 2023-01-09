/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_executer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:27:08 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 12:54:33 by joowpark         ###   ########.fr       */
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
	printf("FUCK\n");
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
