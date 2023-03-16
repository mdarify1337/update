/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:10:22 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 18:14:48 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <termios.h>
# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define STDIN_FILE 0
# define STDOUT_FILE 1

typedef enum e_state
{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}						t_state;

typedef enum e_token
{
	WORD,
	EMPTY,
	GEN_WS,
	WHITE_SPACE = ' ',
	QOUTE = '\'',
	DOUBLE_QUOTE = '\"',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	HERE_DOC,
	DREDIR_OUT,
}						t_oken;

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
	struct s_env_node	*previous;
}						t_env_node;

typedef struct s_env
{
	t_env_node			*first;
	t_env_node			*last;
}						t_env;

typedef struct s_element
{
	char				*content;
	int					len;
	enum e_token		type;
	enum e_state		state;
	struct s_element	*next;
	struct s_element	*previous;
}						t_element;

typedef struct s_list
{
	t_element			*first;
	t_element			*last;
}						t_list;

typedef struct e_cmd_node
{
	char				*args;
	char				**cmd_;
	int					io_in;
	int					io_out;
	int					fcd;
	char				*ferror;
	struct e_cmd_node	*previous;
	struct e_cmd_node	*next;
}						t_cmd_node;

typedef struct e_command
{
	t_cmd_node			*first;
	t_cmd_node			*last;
}						t_command;

typedef struct s_helper
{
	int					count;
	int					(*fd)[2];
	int					i;
	int					status;
	int					start;
	int					end;
	int					proc;
	int					*pid;
}						t_helper;

typedef struct s_main
{
	long long			exit_status;
	t_env				*fenv;
	t_cmd_node			*f_command;
}						t_main;

t_main					g_fcode;
void					minishell(char **envp);
t_list					*init_tokens(t_list *list);
int						get_word(t_list *tokens, char *str, enum e_state state);
t_element				*ft_lstnew(char *content, int len, enum e_token type,
							enum e_state state);
t_list					*lexer(char *line);
char					**ft_split(char const *s, char c);
void					ft_lstadd_back(t_list **list, t_element *new);
int						in_charset(char c);
int						ft_strisspace(char *str);
int						ft_strcmp(char *s1, char *s2);
int						ft_is_alpha(char c);
void					minishell(char **env);
int						ft_isspace(char c);
t_element				*skip_space(t_element *elm, int flag);
int						ft_strcmp(char *s1, char *s2);
void					quotes_state(t_list *tokens, char *str,
							enum e_state *state, enum e_token state2);
int						ft_readline(char **line);
int						tokenize_redir(t_list *tokens, char *str, int i,
							enum e_state *state);
int						get_env_var(t_list *tokens, char *str,
							enum e_state state);
int						is_alphanum(int c);
void					main_program(t_command *node, t_env *env);
void					ft_expand(t_list **lst, t_env *env);
int						check_syntax(t_list *lst);
int						is_closed_quote(t_element *elm);
int						check_quotes(t_list *lst);
int						ft_strchr(char *s, char c);
int						is_redirection(t_element *elm);
size_t					ft_strlen(const char *s);
char					*ft_substr(char *s, int start, int len);
char					*ft_strjoin(char *s1, char *s2);
char					*ft_strdup(char *str);
t_env					*ft_init_env(char **env);
t_env_node				*env_new(char *env);
void					add_env(t_env **env_list, t_env_node *node);
int						delete_node_by_key(t_env *head, char *key);
void					insert_to_tail(t_env **env, t_env_node *new);
t_env_node				*search_by_key(t_env_node *head, char *key);
int						unset_cmd(t_env *env, char *key);
t_command				*parse_command(t_list **list);
char	*ft_strjoin_free2(char *s1, char *s2);
void					export_cmd(t_env *env, char *arg);
char	*ft_realloc(char *old, char *new, t_element *next);
void					ft_cmdadd_back(t_command **list, t_cmd_node *new);
void					update_redirection(t_cmd_node *cmd, t_element *elm);
int						is_pipe(t_element *elm);
int						env_cmd(t_env *env);
int						ft_lstsize(t_env_node *lst);
void					ft_split_args(t_cmd_node **args);
int						check_key(char *key);
int						execute_here_doc(t_list **list);
char					*ft_itoa(int n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strjoin_free(char *s1, char *s2);
void					init_signals(void);
void					ft_cmd_cleaner(t_cmd_node **node);
void					free_2d_array(char **ar);
char					**convert_array(t_env *env);
void					ft_env_cleaner(t_env_node *lst);
void					env_free(t_env_node *lst);
void					ft_lexer_cleaner(t_list *lst);
void					ft_parsing_cleaner(t_list *lst, t_cmd_node *node,
							t_env *env);
void					exec_export(t_cmd_node *cmd, t_env **env);
void					exec_unset(t_cmd_node *cmd, t_env **env);
char					*ft_strndup(char *s1, int n);
// MINISHELL: ------->execution
char					*ft_remove_char(char	*str, char c);
void					export_with_join(t_env **env, char *arg, int i, t_env_node *node_);
char					*ft_strcat(char *s1, char *s2);
char					*ft_strjoin2(char *s1, char *s2);
int						find_path(t_cmd_node **cmd, t_env *env);
int						finitial_variables_commands(t_cmd_node **command,
							t_helper *value, t_env *env);
void					fduplicate_command(t_cmd_node *fd, t_helper *duplicat);
int						flen_linked(char *s);
void					fpclose(t_helper *minishell);
char					**env_arr(t_env_node *env);
void					sig_handler(int sig);
int						ft_isdigit(int c);
void					ft_putendl_fd(char *s, int fd);
int						builtin_exit(char **cmd);
char					**env_arr(t_env_node *env);
void					pwd(void);
void					ft_echo(char **s);
void					ft_exit(char **ex);
int						fcommand_built(t_cmd_node *command);
int						fcalcule_size(t_cmd_node *command);
void					ft_execution_command(t_cmd_node *command, t_env *env);
void					flinked_execution_pipex(t_cmd_node *shell, t_env *env);
void					flinked_send_error(int l, char *command);
void					fcd_command_line(char **paths, t_env *env);
void					flinked_execution_command(t_cmd_node *command,
							t_env *env);
void					fexecute_command(t_cmd_node *minishell, t_env *env);
void					fchild_command_execution(t_cmd_node *data, t_env *env,
							t_helper *val);
int						fbuilt_check_command(t_cmd_node *info, t_env *env);
int						fcheck_execv_builtin(t_cmd_node *info, t_env *env);
void					ft_putstr_fd(char *s, int fd);
void					fprint_ecode(char *s, int fd, int fxcode);
void					ft_parsing_cleaner(t_list *lst, t_cmd_node *node,
							t_env *env);
#endif