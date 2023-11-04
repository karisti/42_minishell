/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:24:30 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/20 16:10:50 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirect_stdin(t_redir *redir)
{
	redir->fd = open_file(redir->str, O_RDONLY);
	if (redir->fd == -1)
		return (0);
	return (1);
}

int	redirect_stdout(t_redir *redir)
{
	int	open_mode;

	if (redir->append)
		open_mode = O_CREAT | O_WRONLY | O_APPEND;
	else
		open_mode = O_CREAT | O_WRONLY | O_TRUNC;
	redir->fd = open_file(redir->str, open_mode);
	if (redir->fd == -1)
		return (0);
	return (1);
}

int	apply_redirections_std(t_command *command)
{
	t_list	*redirs;
	t_redir	*std;

	redirs = command->redirs;
	while (redirs)
	{
		std = (t_redir *)redirs->content;
		if (std->fd < 0)
			return (0);
		if (std->is_input == 1)
			dup2(std->fd, STDIN_FILENO);
		else
			dup2(std->fd, STDOUT_FILENO);
		redirs = redirs->next;
	}
	return (1);
}

void	prepare_redirections_std(t_list *table)
{
	t_list		*cmd_table;
	t_command	*command;
	t_list		*redirs;
	t_redir		*std;

	cmd_table = table;
	while (cmd_table)
	{
		command = (t_command *)cmd_table->content;
		redirs = command->redirs;
		while (redirs)
		{
			std = (t_redir *)redirs->content;
			if (std->is_input)
			{
				if (!redirect_stdin(std))
					return ;
			}
			else
				if (!redirect_stdout(std))
					return ;
			redirs = redirs->next;
		}
		cmd_table = cmd_table->next;
	}
}
