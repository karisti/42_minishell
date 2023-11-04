/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:31:35 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/22 18:13:11 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Creates and initializes 't_command' structure
*/
t_command	*new_command(int id)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
	{
		printf("malloc error\n");
		return (NULL);
	}
	command->id = id;
	command->cmd = NULL;
	command->argv = NULL;
	command->argv_arry = NULL;
	command->argc = 0;
	command->opts = ft_strdup("");
	command->redirs = NULL;
	command->tokens = NULL;
	command->cmd_path = NULL;
	command->pipe.w = -1;
	command->pipe.r = -1;
	return (command);
}

/*
	Creates and initializes 't_redir' structure
*/
t_redir	*new_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_command));
	if (!redir)
	{
		printf("malloc error\n");
		return (NULL);
	}
	redir->str = NULL;
	redir->append = 0;
	redir->fd = -1;
	redir->is_input = 0;
	return (redir);
}

void	free_redirs(void *content)
{
	if (((t_redir *)content)->str != NULL)
		free(((t_redir *)content)->str);
	if (((t_redir *)content)->fd > -1)
		close(((t_redir *)content)->fd);
	if (content != NULL)
		free(content);
}

void	free_argv_arry(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
}

/*
	Free 't_command' struct
*/
void	free_command(void *command)
{
	int			i;
	t_command	*cmd;

	cmd = (t_command *)command;
	if (cmd->cmd != NULL)
		free(cmd->cmd);
	if (cmd->opts != NULL)
		free(cmd->opts);
	i = -1;
	while (cmd->tokens[++i] != NULL)
		free(cmd->tokens[i]);
	free(cmd->tokens[i]);
	if (cmd->tokens != NULL)
		free(cmd->tokens);
	if (cmd->argv != NULL)
		ft_lstclear(&cmd->argv, free);
	ft_lstclear(&cmd->redirs, free_redirs);
	free_argv_arry(cmd->argv_arry);
	free(cmd->cmd_path);
	if (cmd != NULL)
		free(cmd);
}
