/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 12:38:37 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/21 17:51:58 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_no_fork_cmd(t_command *command, t_list *cmd_table)
{
	if (ft_lstsize(cmd_table) > 1)
		return (0);
	if (ft_strcmp(command->cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(command->cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(command->cmd, "export") == 0)
		return (1);
	if (ft_strcmp(command->cmd, "unset") == 0)
		return (1);
	return (0);
}

int	execute_command(t_shell *shell, t_command *command)
{
	pid_t	pid;

	pid = -1;
	if (is_no_fork_cmd(command, shell->cmd_table))
		execute_builtins(shell, command, 0);
	else
	{
		config_sig(&shell->sa, SIG_IGN, SIGINT);
		config_sig(&shell->sa, SIG_IGN, SIGQUIT);
		pid = fork();
		if (pid == 0)
		{
			config_sig(&shell->sa, NULL, SIGINT);
			config_sig(&shell->sa, NULL, SIGQUIT);
			execute_builtins(shell, command, 1);
		}
		else
			close(command->pipe.w);
	}
	restore_io(shell->saved_std);
	if (pid > 0)
		return (1);
	else
		return (0);
}

void	wait_forks(int fork_count)
{
	int	status;

	while (fork_count-- > 0)
	{
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
	}
	if (WIFSIGNALED(status))
		sig_handle_fork(WTERMSIG(status));
}

int	setup_pipe(t_shell *shell, t_command *command, int fd1[2],
	int prev_pipe_read)
{
	command->pipe.r = prev_pipe_read;
	if (shell->cmd_count == 1 || command->id >= shell->cmd_count - 1)
		command->pipe.w = -1;
	else
	{
		if (!create_pipe(shell, &fd1[0]))
			return (0);
		command->pipe.w = fd1[WRITE_END];
		prev_pipe_read = fd1[READ_END];
	}
	return (prev_pipe_read);
}

int	executor(t_shell *shell)
{
	t_list		*list;
	t_command	*command;
	int			fd1[2];
	int			prev_pipe_read;
	int			fork_count;

	fork_count = 0;
	prev_pipe_read = -1;
	list = shell->cmd_table;
	prepare_redirections_std(shell->cmd_table);
	while (list)
	{
		g_exit_status = 0;
		command = (t_command *)list->content;
		prev_pipe_read = setup_pipe(shell, command, &fd1[0], prev_pipe_read);
		if (execute_command(shell, command) == 1)
			fork_count++;
		close_pipe(command);
		if (g_exit_status == 127)
			return (1);
		list = list->next;
	}
	wait_forks(fork_count);
	return (1);
}
