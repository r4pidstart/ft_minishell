LIBFT_SRCS = ft_mylibft

all: $(LIBFT_SRCS)/libft.a
	cc ft_quoteparse1.c ft_quoteparse2.c ft_tester.c ft_error.c ft_cd.c ft_echo.c ft_pwd.c ft_builtin_utils1.c ft_builtin_utils2.c ft_env.c ft_export.c -o test -Wall -Wextra -g3 -ggdb \
	-L$(LIBFT_SRCS) -lft

*.a:
	make -c $(LIBFT_SRCS)