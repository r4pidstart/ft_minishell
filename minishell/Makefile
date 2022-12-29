# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2022/12/29 16:36:29 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -ggdb

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft

PARSE_FOLDER = parse/
BUILTIN_FOLDER = builtin/

SRCS_PARSE = astree.c astree_utils.c ft_free.c ft_str_utils.c \
	  do_cmds.c init.c parse_cmd.c
SRCS_BUILTIN = ft_unset.c ft_quoteparse1.c ft_quoteparse2.c ft_executer.c \
	ft_error.c ft_cd.c ft_echo.c ft_pwd.c ft_builtin_utils.c \
	ft_exit.c ft_env.c ft_export.c

MAIN = ft_main.c ft_envp.c

ifdef BONUS
	NAME = pipex
	FOLDER = bonus/
	SRCS = ft_main_bonus.c ft_piping_bonus.c
else
	FOLDER =
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MAIN:.c:.o) $(addprefix $(PARSE_FOLDER), $(SRCS_PARSE:.c=.o)) $(addprefix $(BUILTIN_FOLDER), $(SRCS_BUILTIN:.c=.o))
	cc $(CFLAGS) \
	-o ./$(NAME) \
	$(MAIN) \
	$(addprefix $(PARSE_FOLDER), $(SRCS_PARSE)) \
	$(addprefix $(BUILTIN_FOLDER), $(SRCS_BUILTIN)) \
	-L$(LIBFT_SRCS) -lft -lreadline
	$(MAKE) clean

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