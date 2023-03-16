NAME		= minishell
	
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -fsanitize=address
RM		= rm -rf

UTILS		= $(addprefix utils/, ft_split linked_list utils utils1 ft_itoa helper)
CLEANER		= $(addprefix cleaner/, parsing_cleaner)
EXPAND		= $(addprefix expander/, expander)
LEXER		= $(addprefix lexer/, lexer lexer_utils)
PARSER		= $(addprefix parser/, parser parser_utils here_doc)
SYNTAX		= $(addprefix check_syntax/, check_quotes syntax_errors)
ENV			= $(addprefix env/, env_operations env_utils env)
MPIPE		= $(addprefix execution/pipex/, command execution  linked pipe command2 execution2 linked2 linked_execution)
BUILTINS	= $(addprefix execution/builtins/, cd_cmd echo_cmd env_cmd exit_cmd export_cmd pwd_cmd unset_cmd export_util)
FILES		= $(addprefix src/, signals main minishell  $(UTILS) $(EXEC) $(CLEANER) $(SYNTAX) $(ENV) $(LEXER) $(PARSER) $(BUILTINS) $(MPIPE) $(EXPAND))
OBJ			= $(FILES:=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -L/usr/local/lib -I/usr/local/include -lreadline $(OBJ) -o $(NAME)

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
