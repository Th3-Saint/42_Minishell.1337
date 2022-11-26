NAME=minishel
CC=gcc
CFLAGS=-Wall -Wextra -Werror #-fsanitize=address -g
SRC	= ./srcs/minishell.c \
	./srcs/Execution/execution.c \
	./srcs/builtins/builtins.c \
	./srcs/utils/utils.c \
	./srcs/Execution/heredoc.c\
	./srcs/Execution/execve.c \
	./srcs/builtins/builtins_utils.c \
	./srcs/builtins/builtins_2.c \
	./srcs/utils/utils_1.c \
	./srcs/utils/utils_2.c \
	./srcs/Execution/open_files.c \
	./srcs/lexer/lexer1.c \
	./srcs/lexer/lexer2.c \
	./srcs/lexer/lexer3.c \
	./srcs/lexer/lexer4.c \
	./srcs/lexer/lexer5.c \
	./srcs/lexer/lexer6.c \
	./srcs/parser/parser1.c \
	./srcs/parser/parser2.c \
	./srcs/parser/parser3.c \
	./srcs/parser/parser4.c 


lib = ./libft/libft.a
OBJS=$(SRC:.c=.o)
readline=-lreadline
LDFLAGS=-L ~/goinfre/.brew/opt/readline/lib
CPPFLAGS=-I ~/goinfre/.brew/opt/readline/include
all:$(NAME)

$(NAME): $(OBJS) $(lib)
	$(CC) -g $(CFLAGS) $(OBJS) $(lib) $(readline)  $(LDFLAGS)  $(CPPFLAGS) -o $(NAME) 
$(lib): 
	make -C ./libft
				
clean:	
	rm -rf $(OBJS)
	make clean -C ./libft

fclean:clean
	rm -rf $(NAME)
	make fclean -C ./libft

re:fclean all
