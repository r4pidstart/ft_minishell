/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 15:10:14 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/10 14:23:26 by joowpark         ###   ########.fr       */
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

void	do_cmd_token(struct s_node *node, int is_in_pipe, int ret)
{
	if (node->right && !node->right->line && is_in_pipe)
		exit(ret);
	if (!node->right && is_in_pipe)
		exit(ret);
}

static struct s_node	*__get_tree(struct s_node *root, char **tokens)
{
	int		ret;
	char	**toks;

	toks = tokens;
	ret = 0;
	while (*tokens && !ret)
	{
		ret = astree_insert_node(root, *tokens, get_type(*tokens));
		tokens += 1;
	}
	if (ret)
	{
		perror(NULL);
		return (NULL);
	}
	free_tokens(toks);
	return (root);
}

struct s_node	*get_tree(char *cmd)
{
	struct s_node	*root;
	char			**tokens;
	int				nr_tokens;

	if (!ft_strncmp(cmd, "&&", 3) || !ft_strncmp(cmd, "||", 3))
		return (ft_alloc_node(cmd, ROOT, NULL));
	else
		root = ft_alloc_node("|", PIPE, NULL);
	if (!root)
		return (NULL);
	tokens = (char **)malloc(sizeof(*tokens) * (ft_strlen(cmd) + 1));
	if (parse_cmd(tokens, cmd, &nr_tokens))
	{
		free_tree(root);
		free_tokens(tokens);
		return (NULL);
	}
	if (!tokens)
		return (NULL);
	return (__get_tree(root, tokens));
}
