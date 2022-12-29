all: fclean
	make -C pipex all
fclean:
	make -C pipex fclean
bonus:
	make -C pipex bonus
t:
	cc test.c -o test