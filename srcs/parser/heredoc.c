/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:09:12 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/18 18:27:59 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	wait_process(char *line)
{
	int	status;

	wait(&status);
	g_exit_status = WEXITSTATUS(status);
	if (WEXITSTATUS(status) == 130)
		return (0);
	if (line != NULL)
		free(line);
	return (1);
}

int	display_heredoc_child(t_shell *shell, char *delimiter, int file)
{
	char	*line;
	int		pid;

	line = NULL;
	pid = fork();
	if (pid == 0)
	{
		config_sig(&shell->sa, sig_handle_heredoc, SIGINT);
		while (1)
		{
			line = readline("> ");
			if (ft_strcmp(line, delimiter) == 0 || !line)
				break ;
			write(file, line, ft_strlen(line));
			write(file, "\n", 1);
			if (line != NULL)
				free(line);
		}
		free(line);
		exit(0);
	}
	return (wait_process(line));
}

/*
	Displays heredoc and each readline is written
	to the temp file 
*/
int	display_heredoc(t_shell *shell, t_command *cmd,
	t_redir *redir, char *delimiter)
{
	char	dir[1024];
	int		file;
	int		process;

	file = -1;
	config_sig(&shell->sa, SIG_IGN, SIGINT);
	config_sig(&shell->sa, SIG_IGN, SIGQUIT);
	if (!getcwd(dir, 1024))
		return (0);
	redir->str = ft_strjoin(dir, TEMP_FILE);
	redir->append = 1;
	redir->is_input = 1;
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	file = open_file(redir->str, O_CREAT | O_WRONLY | O_TRUNC);
	if (file == -1)
		return (0);
	process = display_heredoc_child(shell, delimiter, file);
	close(file);
	return (process);
}
