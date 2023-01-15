NAME  = minishell

SRCS	=	./lib_shell/ft_memset.c \
			./lib_shell/ft_strdup.c \
			./lib_shell/ft_strjoin.c \
			./lib_shell/ft_strlen.c \
			./lib_shell/ft_putstr_fd.c \
			./lib_shell/ft_putchar_fd.c \
			./lib_shell/ft_lstadd_back.c \
			./lib_shell/ft_lstclear.c \
			./lib_shell/ft_lstnew.c \
			./lib_shell/ft_strchr.c \
			./lib_shell/ft_substr.c \
			./lib_shell/ft_isdigit.c \
			./lib_shell/ft_isalpha.c \
			./lib_shell/ft_lstdelone.c \
			./lib_shell/ft_strncmp.c \
			./lib_shell/ft_strcmp.c \
			./lib_shell/lst_node_remove.c \
			./lib_shell/lst_relink.c \
			./lib_shell/ft_isalnum.c \
			./lib_shell/ft_memcpy.c \
			./lib_shell/ft_putnbr_fd.c \
			./lib_shell/ft_split.c \
			./lib_shell/ft_isprint.c \
			./lib_shell/ft_itoa.c \
			./builtin/builtin.c \
			./builtin/echo.c \
			./builtin/pwd.c \
			./builtin/env.c \
			./builtin/cd.c \
			./builtin/unset.c \
			./builtin/export.c \
			./builtin/init_builtin.c \
			./builtin/utils_builtin.c \
			./expander/expander.c \
			./expander/expander_utils.c \
			./exec/exec.c \
			./exec/exec_path.c \
			./exec/exec_pipe.c \
			./exec/exec_child.c \
			./exec/utils_exec.c \
			./exec/exit_status.c \
			./exec/free_all.c \
			./exec/pid_status.c \
			./env/env.c \
			./env/utils_env.c \
			./parsing/parsing.c \
			./parsing/parsing_cmd.c \
			./parsing/parsing_gnl.c \
			./parsing/parsing_heredoc.c \
			./parsing/parsing_pipe.c \
			./parsing/parsing_utils.c \
			./signal/signal.c \
			./lexer/lexer_pipe.c \
			./lexer/lexer_text.c \
			./lexer/lexer.c \
			./lexer/lexer_utils.c \
			./redir/redirection.c \
			./redir/pipes_pid.c \
			./utils/token_utils.c \
			./utils/init_all.c \
			./utils/prompt.c \
			process.c \
			main.c


OBJS= $(SRCS:.c=.o)

INC	=	-I inc

CC	=	clang

CFLAGS	=	-g -Wall -Werror -Wextra
.c.o	:
			${CC} ${CFLAGS} ${INC} -c $< -o ${<:.c=.o}

all : ${NAME}

$(NAME) :	${OBJS}
			${CC} $(CFLAGS) $(OBJS) -o $(NAME) -L/usr/local/lib -I/usr/local/include -lreadline

clean	:	
			rm -rf ${OBJS}

tclean	:	
			rm -rf $(TMP)
			
fclean	:	clean tclean
			rm -rf ${NAME} 

re		:	fclean all

.PHONY	:	all clean fclean re tclean