# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2023/01/05 09:44:38 by joowpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS = -Wall -Wextra -Werror

SRCS = gnl/get_next_line_utils.c gnl/get_next_line.c \
		libft/ft_conversion.c libft/ft_list1.c libft/ft_list2.c libft/ft_memory1.c libft/ft_memory2.c \
		libft/ft_split.c libft/ft_string1.c libft/ft_string2.c libft/ft_string3.c libft/ft_compare.c \
		printf/ft_printf_main.c printf/ft_printf_parse.c printf/ft_printf_print.c printf/ft_printf_utils.c printf/ft_printf_write.c
all: $(NAME)

$(NAME): $(SRCS:.c=.o)
	ar rcs $@ $^

%.o: %.c
	cc $(CFLAGS) -c $^ -o $@

clean:
	rm -rf */*.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
