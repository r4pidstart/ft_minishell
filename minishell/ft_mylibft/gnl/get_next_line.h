/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:26:03 by tjo               #+#    #+#             */
/*   Updated: 2022/08/31 04:49:54 by tjo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include<unistd.h>
# include<stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_fd_list
{
	int					fd;
	int					idx;
	char				*string;
	struct s_fd_list	*next;
}t_fd_list;

/* get_next_line_utils.c */
char	*ft_custom_substr(char const *s, unsigned int start, size_t len);
char	*ft_custom_strjoin(char *s1, char *s2, int rd_siz);

/* get_next_line.c */
char	*get_next_line(int fd);

#endif