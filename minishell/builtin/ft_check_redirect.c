/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:46:33 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 13:28:13 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_builtin_header.h"

int	check_redirect(char **parsed, struct s_node *node, int here)
{
	size_t			cnt;
	char			**cur;
	struct s_node	*node_direct;

	cur = parsed;
	cnt = 0;
	while (*cur)
	{
		cnt++;
		cur++;
	}
	if (cnt > 2)
	{
		redirect_status(1);
		error_handling("minishell", "ambigous redirect", 0);
		return (0);
	}
	node_direct = get_near_type_node(node, REDIRECTS);
	if (!node)
		return (1);	
	return (make_redirection(parsed, &(node_direct->here_doc), here));
}
