/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:47:04 by tjo               #+#    #+#             */
/*   Updated: 2022/12/27 17:28:57 by tjo              ###   ########.fr       */
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
# include"ft_mylibft/libft.h"

# define ENV_FILE "./env.file"

enum e_parser
{
	NORMAL,
	ENV_START,
	SINGLE,
	DOUBLE
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

int		error_handling(char *progname, char *path);
int		echo(char *s);
int		cd(char *s);
int		pwd(void);
int		export(char *s);
int		env(void);

char	*expend_env(char *s);
char	*get_env(char *target);
char	*dummy_string(void);

int		print_all_env(void);
char	**quote_parser(char *);

#endif