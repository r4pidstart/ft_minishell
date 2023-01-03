/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 12:14:32 by joowpark          #+#    #+#             */
/*   Updated: 2023/01/03 18:15:09 by joowpark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../ft_mylibft/libft.h"
# include <fcntl.h>

# define ENVP "/.envp"
# define BUF_SIZE 100

char	*ft_strstrim(char *line);
char	*ft_strndup(char *line, size_t pos);

#endif
