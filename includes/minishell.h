/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 10:15:08 by karisti-          #+#    #+#             */
/*   Updated: 2023/11/04 14:52:49 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# define READ_END 0
# define WRITE_END 1
# define TEMP_FILE "/srcs/.heredoc.tmp"

int	g_exit_status;

typedef struct s_pipe
{
	int			r;
	int			w;
}				t_pipe;

typedef struct s_redir
{
	char		*str;
	int			append;
	int			fd;
	int			is_input;
}				t_redir;

typedef struct s_command
{
	int			id;
	char		**tokens;
	char		*cmd;
	char		*cmd_path;
	t_list		*argv;
	char		**argv_arry;
	int			argc;
	char		*opts;
	t_list		*redirs;
	t_pipe		pipe;
}				t_command;

typedef struct s_shell
{
	char				*line;
	char				*line_str;
	char				**env;
	t_list				*env_list;
	t_list				*cmd_table;
	int					cmd_count;
	struct sigaction	sa;
	int					saved_std[2];
}				t_shell;

// main.c
void		print_command(t_list *lst);

// init_shell.c
void		init_shell(t_shell *shell, char **env);
int			free_shell(t_shell *shell, int ret);
void		reset_shell(t_shell *shell);

// prompt.c
int			display_prompt(t_shell *shell);
void		end_prompt(t_shell *cmd);

// command_table.c
t_command	*new_command(int id);
t_redir		*new_redir(void);
void		free_command(void *command);

// parser.c
int			parse(t_shell *shell, int i);

// options.c
void		add_cmd_options(t_command *cmd, char *opts);
int			valid_option(char *opts);

// check_syntax.c
int			check_syntax(t_shell *shell);

// tokens.c
int			merge_tokens(t_command *cmd, int pos);

// quotes.c
int			manage_quotes(t_shell *shell, char **str);

// expand_envs.c
void		expand_envs(t_shell *shell, char **token);

// redirections.c
char		*fix_redirection_spaces(char *str);
int			get_redirections(t_shell *shell, t_command *cmd,
				char **array, int i);
int			is_redirection(char *str);

// heredoc.c
int			display_heredoc(t_shell *shell, t_command *cmd,
				t_redir	*redir, char *delimiter);

// ft_split_no_quotes.c
char		**ft_split_no_quotes(char const *s, char c);

// ft_split_two.c
char		**ft_split_two(char *str, char c);

// ft_strjoin_free.c
char		*ft_strjoin_free(char *s1, char *s2);

// ft_isalnum_underscore.c
int			ft_isalnum_underscore(char *str);

// envs.c
char		*get_env_value(t_shell *shell, char *key);
int			update_env(t_shell *shell, char *env);
void		del_from_env_list(t_shell *shell, char *key);
void		update_envs_str(t_shell *shell, t_list *envs_list);

// signals.c
void		sig_handle(int signum);
void		sig_handle_fork(int signum);
void		sig_handle_heredoc(int signum);
void		config_sig(struct sigaction *sa, void (*handler)(int), int sig);

// exec.c
int			executor(t_shell *cmd_table);
void		execute_builtins(t_shell *shell, t_command *command,
				int is_fork);
void		restore_io(int saved_std[2]);

// pipes.c
int			create_pipe(t_shell *shell, int *fd1);
void		close_pipe(t_command *command);
void		redirect_pipe(t_command *command);

// redirections.c
void		prepare_redirections_std(t_list *table);
int			apply_redirections_std(t_command *command);

// files.c
int			open_file(char *path, int mode);
int			check_file(char *path);

// errors.c
int			put_error(int errornum, char *errormsg, int ret);

// str_is_number.c
int			str_is_number(char *str);

// ft_strstrlen.c
int			ft_strstrlen(char **str);

// ft_cd.c
void		ft_cd(t_shell *shell, t_command *command);

// ft_pwd.c
void		ft_pwd(void);

// ft_env.c
void		ft_env(t_shell *shell);
void		print_envs_list(void *node_content);

//ft_export.c
void		ft_export(t_shell *shell, t_command *command);

// ft_unset.c
void		ft_unset(t_shell *shell, t_command *command);

// ft_echo.c
void		ft_echo(t_command *command);

// ft_exit.c
void		ft_exit(t_shell *shell, t_command *command, int is_fork);

void		print_test(void *content);

#endif
