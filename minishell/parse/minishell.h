/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:10:35 by joowpark          #+#    #+#             */
/*   Updated: 2022/12/29 16:09:08 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "astree.h"
# include "parse.h"

# define MINISHELL "minishell: "
int		init_envp(void);
char	**get_envp(void);
void	free_tree(struct s_node *node);
int		do_cmds(char **tokens);
int		parse_cmd(char **tokens, char *cmd, int *nr_tokens);

#endif
