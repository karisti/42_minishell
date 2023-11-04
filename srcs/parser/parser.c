/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 13:46:39 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/22 18:17:09 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	parse_redir(t_shell *shell, t_command *command, int redir, int i)
{
	redir = is_redirection(command->tokens[i]);
	if (redir == 1)
	{
		if (!command->tokens[i + 1]
			|| is_redirection(command->tokens[i + 1]) == 1)
		{
			put_error(1, "syntax error", -42);
			return (-42);
		}
		expand_envs(shell, &command->tokens[i + 1]);
		if (!manage_quotes(shell, &command->tokens[i + 1]))
			return (-42);
		redir = get_redirections(shell, command, command->tokens, i);
	}
	return (redir);
}

/*
	Parses single token to 't_command' struct

	Next 'i' index is returned if OK, -42 if error
*/
int	parse_token(t_shell *shell, t_command *command, int i, int expansion)
{
	int	redir;

	redir = 0;
	if (!manage_quotes(shell, &command->tokens[i]))
		return (-42);
	if (expansion == 0)
		redir = parse_redir(shell, command, 0, i);
	if (redir < 0)
		return (-42);
	if (redir > 0)
		i += redir;
	else if (!command->cmd)
		command->cmd = ft_strdup(command->tokens[i]);
	else if (command->cmd && !command->argv && valid_option(command->tokens[i]))
		add_cmd_options(command, command->tokens[i]);
	else
	{
		ft_lstadd_back(&command->argv,
			ft_lstnew(ft_strdup(command->tokens[i])));
		command->argc++;
	}
	return (i);
}

/*
	Parses single command tokens to the 't_command'
	struct, that is going to be used by
	the executor.

	1 is returned if OK, 0 if error
*/
int	parse_str_to_cmd(t_shell *shell, t_command *command)
{
	int	i;
	int	expansion;

	i = -1;
	expansion = 0;
	while (command->tokens[++i])
	{
		if (expansion < 0)
			expansion = 0;
		if (ft_strchr(command->tokens[i], '$'))
		{
			expand_envs(shell, &command->tokens[i]);
			if (ft_strlen(command->tokens[i]) > 0)
				expansion = merge_tokens(command, i);
		}
		if (ft_strlen(command->tokens[i]) > 0)
			i = parse_token(shell, command, i, expansion--);
		if (i == -42)
			return (0);
	}
	return (1);
}

/*
	Splits user input by '|' and saves all
	potential command in the 'sp_cmds' array
*/
void	split_pipes(t_shell *shell, char ***sp_cmds)
{
	char	*aux;
	int		i;

	*sp_cmds = ft_split_no_quotes(shell->line, '|');
	i = -1;
	while ((*sp_cmds)[++i])
	{
		aux = (*sp_cmds)[i];
		(*sp_cmds)[i] = ft_strtrim(aux, " ");
		free(aux);
	}
}

/*
	Splits by '|' to separate each
	potential command.
	After this, it parses to 't_command'
	structure and adds to command table.
*/
int	parse(t_shell *shell, int i)
{
	t_command	*cmd;
	char		**sp_cmds;

	split_pipes(shell, &sp_cmds);
	while (sp_cmds[++i])
	{
		if (ft_strlen(sp_cmds[i]) <= 0)
			return (put_error(1, "syntax error", 0));
		cmd = new_command(i);
		if (!cmd)
			return (0);
		ft_lstadd_back(&shell->cmd_table, ft_lstnew(cmd));
		sp_cmds[i] = fix_redirection_spaces(sp_cmds[i]);
		cmd->tokens = ft_split_no_quotes(sp_cmds[i], ' ');
		free(sp_cmds[i]);
		if (!parse_str_to_cmd(shell, cmd))
		{
			free(sp_cmds);
			return (0);
		}
		shell->cmd_count++;
	}
	free(sp_cmds);
	return (1);
}
