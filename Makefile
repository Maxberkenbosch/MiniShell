NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPILE = $(CC) $(CFLAGS)
LIBFT = ./libft
LIB = $(LIBFT)/libft.a

INCLUDES =	-I/Users/ajanse/homebrew/opt/readline/include\
			-I./includes\
			-I$(LIBFT)

LIBDIRS =	-L/Users/ajanse/homebrew/opt/readline/lib\
			-L$(LIBFT)

LIBS =	-lreadline\
		-lft

SDIR = ./src
SRCS =	minishell.c\
		minishell_utils.c\
		excecute.c\
		get_file_name.c\
		parse.c\
		redirect.c\
		add_path.c\
		check_tokens.c\
		remove_redirections.c\
		expansions_utils.c\
		expansions.c\
		ft_split_shell.c\
		ft_split_cmd.c\
		heredoc.c\
		cd.c\
		env_export.c\
		env_unset.c\
		utils_max.c\
		ft_env.c\
		ft_pwd.c\
		ft_pipex.c\
		ft_dups.c\
		ft_echo.c\
		ft_exit.c\
		strip_quote.c\
		ft_getenv.c\
		signals.c\
		redirect_utils.c

ODIR = ./obj
OBJS = $(patsubst %,$(ODIR)/%,$(SRCS:.c=.o))

$(ODIR)/%.o : $(SDIR)/*/%.c
	@mkdir -p obj
	@echo "Creating object : $@"
	@$(COMPILE) $(INCLUDES) -c -o $@ $<

all: libft | $(NAME)

$(NAME): $(LIB) $(OBJS)
	@echo "Creating executable $(NAME)"
	@$(COMPILE) $(OBJS) $(LIBDIRS) $(LIBS) -o $(NAME)

run: $(NAME)
	@./$<
	@echo "Worked just fine"

clean:
	@echo "Removing object files $(NAME)"
	@rm -rf $(OBJS) $(ODIR)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@echo "Removing executable file $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

libft:
	@$(MAKE) -C $(LIBFT)

re: fclean | all

.PHONY: all clean fclean libft run re
