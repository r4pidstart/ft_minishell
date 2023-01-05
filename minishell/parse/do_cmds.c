/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joowpark <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:10:14 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/05 12:21:02 by joowpark         ###   ########.fr       */
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
	int		is_in_pipe;
	int		ret;
	size_t	idx;

	is_in_pipe = 0;
	search_tree(root, &is_in_pipe, &ret);
	idx = 0;
	while (idx ++ < root->depth)
		waitpid(-1, NULL, 0);
	free_tree(root);
	return (ret);
}

void	do_cmd_token(struct s_node *node, int is_in_pipe, int ret)
{
	if (node->right && !node->right->line && is_in_pipe)
		exit(ret);
	if (!node->right && is_in_pipe)
		exit(ret);
}

int	do_cmds(char **tokens)
{
	struct s_node	*root;
	int				ret;

	ret = 0;
	root = ft_alloc_node("|", PIPE, NULL);
	if (!root)
		return (1);
	while (*tokens)
	{
		if (astree_insert_node(root, *tokens, get_type(*tokens)))
		{
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
