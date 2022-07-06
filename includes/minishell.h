#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "Minishell>> "
# define EOF -1

typedef struct s_pipex
{
	int	new_pipe[2];
	int	last_pipe;
	int	am_cmds;
	int	iter;
	int	heredoc;
}	t_pipex;

typedef struct s_minishell
{
	char	*line;
	char	**cmds;
	char	**env;
	int		exit_code;
	int		stdin_fd;
	int		stdout_fd;
	int		sig;
	t_pipex	pipex;
}	t_minishell;

typedef struct s_heredoc
{
	int		end[2];
	int		old_out;
	char	*line;
	char	*delimiter;
}	t_heredoc;

//Syscalls
int		ft_execsys(char **cmd_words, t_minishell *minishell);
void	ft_dupstds(int in, int out);
int		ft_pipex(char **cmds, t_pipex pipex, t_minishell minishell);

//Parse and lex
int		handle_cmd(char *cmd, t_minishell *minishell, int piped);
char	**add_path(char **cmd, char **env);
int		check_tokens(char *line, t_minishell *minishell);
char	**ft_split_shell(char *s, char c);
void	parse(t_minishell *minishell);
char	**ft_split_cmd(char const *s, char c);

//Environment vars
char	**make_new_array(t_minishell *minishell, char *new_element);
char	**make_env(char **env);
char	*ft_getenv(char *var, t_minishell *minishell);

//Expansions
char	*expansions(char *s, t_minishell *minishell);
int		conv_vars(char **vars, t_minishell *minishell);
void	sub_vars(char *new_s, char *s, char **vars);
char	*check_var(char *s);
char	*ft_strchr_var(const char *s, int c);

//Built in
int		search_builtin(char **cmd_words, t_minishell *minishell);
int		ft_export(char **cmd_words, t_minishell *minishell);
int		ft_cd(char *path, t_minishell *minishell);
int		ft_unset(char **cmd_words, t_minishell *minishell);
int		ft_env(t_minishell *minishell);
int		ft_pwd(t_minishell *minishell);
int		ft_echo(char **cmd_words);
int	ft_exit(char **cmd_words, int am_cmds);
int		valid_identifier_export(char *cmd_word, t_minishell *minishell);
int		valid_identifier_unset(char *cmd_word, t_minishell *minishell);

//Utils
char	*ft_strdup_shell(const char *s1);
char	*ft_strjoin_shell(char const *s1, char const *s2);
char	*strip_quotes(char *s);
char	*skip_quote(char *s, int *i);
char	*skip_whitespace(char *line);
int		error_handle(char const *s);

//Signals
void	signals(void);
void	sigint_handler_in_process(int sig);
void	sigquit_handler_in_process(int sig);
void	sigint_handler_heredoc(int sig);
void	sig_in_process(char *cmd);

//Redirections
char	*redir_in(char *s, t_minishell *minishell);
char	*redir_out(char *s, t_minishell *minishell);
char	*redir_append(char *s, t_minishell *minishell);
char	*heredoc(char *s, t_minishell *minishell);
int		redirections(char *s, t_minishell *minishell, int piped);
char	*remove_redirections(char *s);
char	*get_file_name(char *s);

#endif