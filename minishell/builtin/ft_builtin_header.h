/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_header.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 11:47:04 by tjo               #+#    #+#             */
/*   Updated: 2022/12/26 18:04:45 by tjo              ###   ########.fr       */
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

int		error_handling(char *progname, char *path);
int		echo(char *s);
int		cd(char *s);
int		pwd(void);

char	*get_env(char *target);
char	*dummy_string(void);

#endif