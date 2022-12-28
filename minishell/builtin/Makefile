# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2022/12/28 20:54:00 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test
CFLAGS = -Wall -Wextra -g3 -ggdb#-Werror -g3 -ggdb

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft
SRCS = ft_unset.c ft_quoteparse1.c ft_quoteparse2.c ft_executer.c \
ft_error.c ft_cd.c ft_echo.c ft_pwd.c ft_builtin_utils.c \
ft_exit.c ft_env.c ft_export.c

ifdef BONUS
	NAME = pipex
	FOLDER = bonus/
	SRCS = 
else
	FOLDER = ./
endif

all: $(NAME)

$(NAME): $(LIBFT) $(addprefix $(FOLDER), $(SRCS:.c=.o))
	cc $(CFLAGS) \
	-o ./$(NAME) \
	$(addprefix $(FOLDER), $(SRCS)) \
	-L$(LIBFT_SRCS) -lft

$(LIBFT):
	make -C $(LIBFT_SRCS) all

%.o: %.c
	cc $(CFLAGS) -c $^ -o $@
	
bonus:
	$(MAKE) BONUS=1

clean:
	rm -rf */*.o
	rm -rf *.o
	make clean -C $(LIBFT_SRCS)
	
fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_SRCS)

re: fclean all

.PHONY: bonus all clean fclean re