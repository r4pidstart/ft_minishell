/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:47:04 by tjo               #+#    #+#             */
/*   Updated: 2022/12/30 17:05:27 by tjo              ###   ########.fr       */
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

int		builtin_executer(char *s);
int		error_handling(char *progname, char *custom_msg, char *path);
int		make_redirection(char **s);

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

// ../t_envp.c
char	**get_envp_ptr(void);
char	*get_env_path(void);
char	**get_envp(void);

#endif