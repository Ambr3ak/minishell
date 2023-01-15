/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:20:27 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:20:33 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

//GLOBAL
# define ERROR      -1
# define INPUT_MAX 4096
# define MINISHELL "Minishell"
# define WHITE_SPACE " \t\n"

//ERROR CODE
# define ERROR_LEXER    -1
# define ERROR_QUOTE    "Quote non fermes"
# define ERROR_PIPE     "Pipe incomplet"
# define ERROR_REDIR    "Redirection incomplete"
# define ERROR_MEMORY   "out of memory"
# define ERROR_HEREDOC  "Mauvaise syntax heredoc"
# define ERROR_ERRNO    -6
# define ERROR_ENOMEM   -7
# define ERROR_ENV "Environnement non valable"
# define ERROR_UNSET "Identifiant non valable"
# define ERROR_CD_1 "Trop d'arguments"
# define ERROR_CD_2 "Aucun fichier ou dossier de ce type"
# define CMD_NOT_FOUND "command not found"

//LEXER PARSER CODE
# define TOKEN_TEXT         1
# define TOKEN_QUOTE        34
# define TOKEN_REDIR        62
# define TOKEN_PIPE         128
# define TOKEN_REDIR_FILE   256
# define TOKEN_HEREDOC      512
# define TOKEN_CONNECTED    1024
# define TOKEN_S_QUOTE        2048
# define TOKEN_D_QUOTE        4096
# define CMD_SCMD       1
# define CMD_PIPE       2
# define CMD_PIPELINE   4

//REDIR CODE
# define REDIR_OUT      1
# define REDIR_OUT_APP  2
# define REDIR_IN       3
# define REDIR_HEREDOC  4

//EXEC CODE
# define ABSOLUT_PATH 1
# define SCRIPT 1
# define OUT 1
# define IN 0

//GLOBAL
extern char	**g_env;

//STRUCTURES
typedef struct s_red_fds
{
	int	in;
	int	out;
}				t_red_fds;

typedef struct s_rec
{
	int	i;
	int	**fd;
	int	*id;
	int	counter;
	int	*can_exec;
}				t_rec;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_cmd
{
	char	*tk;
	int		flag;
}				t_cmd;

typedef struct s_data
{
	t_list		*l_token;
	t_list		*history;
	t_rec		*r;
	t_red_fds	*fds;
	char		**path;
	char		*pwd;
	int			env_size;
	int			argc;
	int			path_i;
	int			absolut_path;
	int			fd_in;

}				t_data;

typedef struct s_p_cmd
{
	int		type;
	t_list	*l_argv;
	t_list	*l_redir;
}				t_p_cmd;

typedef struct s_merge_cmd
{
	int		type;
	t_list	*l_element;
}				t_m_cmd;

//LIB_SHELL
void		*ft_memset(void *b, int c, size_t len);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strdup( char *s1);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isprint(int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_isalnum(int c);
void		ft_putnbr_fd(int x, int fd);
char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char *s, unsigned int start, size_t len);
int			ft_d_strlen(char **s);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		*ft_strjoin_buff(char *s1, char c);
char		*ft_itoa(int n);

//UTILS
void		init_cmd(char **s);
int			init_path(t_data *env, char *cmd);
char		**token_to_array(int *argc, t_list *scmd);
int			init_size(t_list *scmd, int *argc);
int			init_value(char **env_name, char **tmp, int *name_size);
//PROMPT
char		*prompt_str(void);

//LEXER
int			redir_token(char *input, t_list **token, int *i);
int			pipe_token(char *input, t_list **token, int *i);
int			text_token(char *input, t_list **token, int *i);
int			quote_token(char *input, t_list **token, int *i);
int			size_quote(char *s);
int			size_txt(char *s);
int			is_other(char *s);
t_list		*lexer(char *cmd_input);
t_list		*check_syntax(t_list *token);
t_cmd		*tok_struct(t_list *token);
t_list		*liste_add_token(char *text, int type);

//BUILTIN
char		*is_builtin(char *arr);
int			echo(char **cmd, int argc);
int			pwd(void);
int			env(char **g_env);
int			exit_b(char **token, t_data *env, t_list *scmd);
int			unset(char **argv, t_data *env);
int			cd(char **argv, int argc);
int			export(char **argv, t_data *env);
int			export_plus_equal(char *var);
int			size_alloc(char **s, int index);
void		init_new_pwd(char **new_env, char ***s);
void		init_pwd(char **new_pwd, char **old_pwd, char ***new_env, char **s);
void		sort(char **g_env);
void		init_new_pwd(char **new_env, char ***s);

//EXPANDER
int			expander(t_list *argv, t_list *redir);
int			expand_str_exit_code(char **var);
void		del_empty_tok(t_list *cmd);
int			unexisted_var(char *env_name);

//EXEC
int			exec_scmd(t_list *scmd, t_data *env);
void		add_to_history(char **input, t_list **history);
int			exec_builtin(char **token, t_data *env_s);
//exec_path
int			get_path(t_data *env, char **cmd);
int			exec_pipe(t_list *cmd, t_data *env);
int			lst_size(t_list *lst);
int			counter(t_list *cmd);
int			history(t_list *history);
//exec_child
int			wait_pid(t_rec *recup, int count);
int			child(int *fd_s, t_list **l_element, char ***cmd, t_data *env);
void		exit_child(t_data *env, char *cmd_arr, int status);
//utils_exec
t_red_fds	*init_std(void);
t_rec		*init_process(int count, t_rec *r);
char		***init_pipe_cmd(t_list *l_element, int count);
char		**del_empty_token(char ***token);
//exit_status
void		exec_last_return_set(int status);
int			exec_last_ruturn_get(void);
int			last_pid_get(void);
void		last_pid_set(int i);

//REDIR
int			select_redir(char *redir);
int			redir_in(t_list *redir);
int			redir_out(t_list *redir);
int			redir_out_app(t_list *redir);
void		restore_fds(t_red_fds *fds);
int			redir_process(t_list *redir, t_red_fds *fds);
int			perform_scmd(t_list *redir);
int			perform_redir(t_list *redir);
int			perform_heredoc(t_list *redir);
int			redir_heredoc(t_list *redir);

//ENV
char		**get_env(t_data *env, char **envp);
char		*get_env_value(char *env_name);
int			find_index_var(char *var_name);
char		*find_var(char *var);
void		add_char(char ***s, char *added);
void		join_old_var(char *var_name, char ***g_env);
void		print_env(char **g_env);
char		*get_env_value_1(char *env_name, int *status);

//ERROR
int			print_error(char *shell_name, char *cmd, char *error);

//PARSING
t_list		*parsing(t_list *token);
t_list		*parsing_cmd(t_list *token);
int			set_cmd_type(t_list *token);
t_list		*create_p_cmd(int type);
void		p_cmd_destroy(void *tmp);
void		c_token_destroy(void *c_token);
t_p_cmd		*p_cmd_struct(t_list *pcmd);
int			redir_type(char *redir);
char		*token_to_str(t_list *token);
char		*str_add_chr(char *str, char chr);
char		*str_add_str(char *str, char *s2);
char		*minishell_get_next_line(int fd);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			lst_node_remove(t_list **lst, t_list *node, void (*del)(void *));
int			heredoc_parse(t_list *token);
int			cmd_pipe_merge(t_list **cmd);
t_list		*lst_node_prev(t_list *lst, t_list *node);
int			lst_relink(t_list **lst, t_list *node, t_list *start, t_list *end);
t_m_cmd		*cmd_struct(t_list *cmd);
t_list		*create_m_cmd(int type);
void		m_cmd_destroy(void *m_cmd);
void		print_struct(t_list *cmd);
void		print_debug_pipe(t_list *cmd);
void		print_debug_cmd(t_list *cmd);
int			m_cmd_type(t_list *cmd);
void		init_input_signals(void);
void		minishell_exit(void);
int			token_flag(t_list *token);
int			parser_pipe_merge(t_list **cmd);

//SIGNAL
void		ctrl_c_handle(int signal);
void		ctrl_c_herdoc_handle(int signal);
void		init_exec_signals(void);
int			wait_one_pid(int last_pid);
void		sigquit_handler(int signal_value);
void		exec_ctrl_c_handle(int signal_value);

//FREE
void		free_cmd(char ***cmd);
void		free_d_char(char **s);
void		free_path(char *cp, char *tmp, t_data *env);
void		f_t_char(char ***s);
void		free_env(t_data *env);

//PROCESS
char		*get_bytes_rl(void);
t_list		*process(char *cmd_input);
void		init_env(t_data *env);
int			executer(t_list *cmd, t_data *env);
#endif
