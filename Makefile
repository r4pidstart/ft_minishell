all: fclean
	make -C minishell all
fclean:
	make -C minishell fclean
bonus:
	make -C minishell bonus
t:
	cc test.c -o test