# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjo <tjo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 12:48:31 by tjo               #+#    #+#              #
#    Updated: 2023/01/04 00:54:42 by tjo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror -g3 -ggdb #-fsanitize=address

LIBFT = ft_mylibft/libft.a
LIBFT_SRCS = ft_mylibft

PARSE_FOLDER = parse/
BUILTIN_FOLDER = builtin/

SRCS_PARSE = astree.c astree_utils.c ft_free.c ft_str_utils.c \
	  do_cmds.c parse_cmd.c ft_check_tokens.c
SRCS_BUILTIN = ft_unset.c ft_quoteparse1.c ft_quoteparse2.c ft_executer.c \
	ft_error.c ft_cd.c ft_echo.c ft_pwd.c ft_builtin_utils.c \
	ft_exit.c ft_env.c ft_export.c ft_fork_execve.c ft_make_redirection.c \
	ft_pipe.c

uname := $(shell uname -p)
ifeq ($(uname), arm)
	__LDFLAGS="-L/opt/homebrew/opt/readline/lib"
	__CPPFLAGS="-I/opt/homebrew/opt/readline/include"
else
	__LDFLAGS="-L$(HOME)/.brew/opt/readline/lib"
	__CPPFLAGS="-I/$(HOME)/.brew/opt/readline/include"
endif

MAIN = ft_main.c ft_envp.c

# ifdef BONUS
# 	NAME = 
# 	FOLDER = bonus/
# 	SRCS = 
# else
# 	FOLDER =
# endif

all: $(NAME)

$(NAME): $(LIBFT) $(MAIN:.c:.o) $(addprefix $(PARSE_FOLDER), $(SRCS_PARSE:.c=.o)) $(addprefix $(BUILTIN_FOLDER), $(SRCS_BUILTIN:.c=.o))
	cc $(CFLAGS) \
	-o ./$(NAME) \
	$(MAIN) \
	$(addprefix $(PARSE_FOLDER), $(SRCS_PARSE)) \
	$(addprefix $(BUILTIN_FOLDER), $(SRCS_BUILTIN)) \
	-L$(LIBFT_SRCS) -lft  -lreadline $(__LDFLAGS) $(__CPPFLAGS)
	# $(MAKE) clean

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
	make re -C $(LIBFT_SRCS)

.PHONY: bonus all clean fclean re
