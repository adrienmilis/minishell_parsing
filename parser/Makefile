SRCS = parser.c \
	utils.c \
	main.c \
	errors.c \
	linked_list.c \
	libft.c \
	add_arguments.c \
	check_chars.c \
	check_syntax.c \
	parse_out_quotes.c \
	env.c \
	env_vars.c \
	simple_quotes.c \
	check_chars2.c

SRCS_TEST = parser.c \
	utils.c \
	tester.c \
	errors.c \
	linked_list.c \
	libft.c \
	add_arguments.c \
	check_chars.c \
	check_syntax.c \
	parse_out_quotes.c \
	env.c \
	env_vars.c \
	simple_quotes.c \
	check_chars2.c

OBJS = $(SRCS:.c=.o)
OBJS_TEST = $(SRCS_TEST:.c=.o)

NAME = minishell

FLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS)
	gcc $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)
	
test: $(OBJS_TEST)
	gcc $(FLAGS) $(OBJS_TEST) -o $(NAME)

clean:
	rm -rf $(OBJS) tester.o

fclean: clean
	rm -rf $(OBJS)

re: fclean all