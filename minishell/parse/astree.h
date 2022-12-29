/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:54:55 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 16:09:12 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

# include "types.h"

enum e_type{
	ROOT,
	PIPE,
	CMD,
	REDIRECTS,
	REDIRECT,
	SIMPLE_CMD,
};

enum e_dirtype
{
	HERE_DOC,
	OUT,
	IN,
	ADD_OUT,
};

struct s_node{
	char			type;
	char			*line;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
	size_t			depth;
};

void			search_tree(struct s_node *node);
struct s_node	*ft_get_cmd_token(struct s_node *root);
void			astree_init(struct s_node *root);
struct s_node	*ft_alloc_node(char *line, char type);
int				astree_insert_node(struct s_node *root, char *line, char type);

int		builtin_executer(char *s);

#endif
