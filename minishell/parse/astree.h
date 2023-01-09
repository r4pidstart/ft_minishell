/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:54:55 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/09 15:29:10 by joowpark         ###   ########.fr       */
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
	NON_PIPE,
};

struct s_node{
	char			type;
	char			*line;
	char			**cmd;
	struct s_node	*left;
	struct s_node	*right;
	size_t			depth;
	struct s_node	*root;
	struct s_node	*parent;
	int				std_inout[2];
	char			*here_doc;
};

struct s_node	*get_tree(char *tokens);
struct s_node	*get_near_type_node(struct s_node *node, int type);
void			do_cmd_token(struct s_node *node, int is_in_pipe, int ret);
void			search_tree(struct s_node *node, int *is_in_pipe, int *ret);
struct s_node	*ft_get_cmd_token(struct s_node *root);
void			astree_init(struct s_node *root);
struct s_node	*ft_alloc_node(char *line, char type, struct s_node *node);
int				astree_insert_node(struct s_node *root, char *line, char type);
void			pre_search_tree(struct s_node *node, int *ret);
int				builtin_executer(struct s_node *node, char *s, int is_in_pipe);
int				ft_pre_executer(char *s, struct s_node *node);
#endif
