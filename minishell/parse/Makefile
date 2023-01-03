NAME= mini

CC= cc
ADR = ./
SRC = astree.o astree_utils.o ft_free.o ft_str_utils.o \
	  do_cmds.o init.o parse_cmd.o main.o

SRCS = ${addprefix ${ADR}, ${SRC}}

BONUS= $(NAME)

OFLAGS = -fsanitize=address
CFLAGS += $(OFLAGS)
CFLAGS +=  -Wall -Wextra -Werror -g3 -ggdb
CFLAGS +=  -I ./include 
all : $(NAME)

LIBFTA = ./libfta/libft.a

all : $(NAME)

$(NAME): $(SRC)
	$(MAKE) -C ./libfta 
	$(CC) $(CFLAGS) ${LIBFTA} $^ -o $@ -g3 -lreadline

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@ -g3 

.PHONY: libft
libft :
	$(MAKE) -C libfta re

.PHONY : clean
clean:
	rm -f ${SRCS}
	$(MAKE) -C libfta clean

.PHONY : fclean

fclean : clean
	rm -f ${NAME} 

.PHONY : re
re : 
	$(MAKE) fclean 
	$(MAKE) all
