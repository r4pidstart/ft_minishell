/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:10:35 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/03 09:23:43 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "types.h"
# include "astree.h"
# include "parse.h"

# define MINISHELL "minishell: "


int		check_pipe(char **lines);
int		init_envp(void);
char	**get_envp_ptr(void);
void	free_tree(struct s_node *node);
int		do_cmds(char **tokens);
int		parse_cmd(char **tokens, char *cmd, int *nr_tokens);
void	free_tokens(char **tokens);

#endif
