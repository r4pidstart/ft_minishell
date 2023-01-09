/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:47:04 by tjo               #+#    #+#             */
/*   Updated: 2023/01/09 13:35:43 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BUILTIN_HEADER_H
# define FT_BUILTIN_HEADER_H

# include<stdlib.h>
# include<unistd.h>
# include<dirent.h>
# include<errno.h>
# include<string.h>
# include<fcntl.h>
# include"../ft_mylibft/libft.h"
# include "../parse/astree.h"

# define STDIN_BACKUP 254
# define STDOUT_BACKUP 255

enum e_parser
{
	NORMAL,
	ENV_START,
	SINGLE,
	DOUBLE
};

enum e_redirect
{
	R_NORMAL,
	R_OUTPUT,
	R_APPEND,
	R_INPUT,
	R_HERE_DOC
};

typedef struct s_parser
{
	char	*ret;
	int		s;
	int		e;
	int		status;
}t_parser;

typedef struct s_get_env
{
	char	*target;
	char	*tmp;
	char	*env;
	char	*ret;
	int		env_fd;
}t_get_env;

int		builtin_executer(struct s_node *node, char *s, int is_in_pipe);
int		error_handling(char *progname, char *custom_msg, char *path);
int		make_redirection(char **s, char **node_line, int here);
int		exit_code_export(int ret);

int		fork_execve(char **parsed);
int		echo(char **s);
int		cd(char **s);
int		pwd(char **s);
int		export(char **s);
int		env(char **s);
int		unset(char **s);
int		ft_exit(char **s);

char	*get_heredoc_path(void);
char	*expend_env(char *s);
char	*get_env(char *target);
char	*dummy_string(void);

int		print_all_env(void);
char	**quote_parser(char *s);
char	*line_env_expender(char *s);

// ../ft_envp.c
char	**get_envp_ptr(void);
char	*get_env_path(void);
char	**get_envp(void);

int		check_redirect(char **parsed, struct s_node *node, int here);
int		redirect_status(int cmd);

int		make_pipe(struct s_node *node);
int		non_fork_execve(char **parsed);

int		wildcard_parser(char ***parsed);
int		reorder_parsed(char ***parsed);
int		free_parsed(char **parsed);

void	get_input_line(struct s_node *node,int is_in_pipe);
int		ft_pre_executer(char *s, struct s_node *node);
#endif
