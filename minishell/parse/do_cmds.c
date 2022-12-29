/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:10:14 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/28 16:11:12 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "astree.h"

static char	get_type(char *line)
{
	if (*line == '<' || *line == '>')
		return (REDIRECT);
	else if (*line == '|')
		return (PIPE);
	else
		return (SIMPLE_CMD);
}

static int	do_tree(struct s_node *root)
{
	search_tree(root);
	free_tree(root);
	return (0);
}

int	do_cmds(char **tokens)
{
	struct s_node	*root;
	int				ret;

	ret = 0;
	root = ft_alloc_node(NULL, ROOT);
	if (!root)
		return (1);
	while (*tokens)
	{
		if (astree_insert_node(root, *tokens, get_type(*tokens)))
		{
			printf("%d :[%s]\n", get_type(*tokens), *tokens);
			ret = 1;
		}
		if (ret)
			break ;
		tokens += 1;
	}
	if (ret)
	{
		perror(NULL);
		return (ret);
	}
	return (do_tree(root));
}
