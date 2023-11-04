/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:07:52 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/21 15:59:00 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	tokens_created(char **new_tokens, int new_toks_size)
{
	if (new_toks_size < 2)
	{
		if (new_tokens && new_tokens[0])
			free(new_tokens[0]);
		if (new_tokens)
			free(new_tokens);
		return (0);
	}
	return (1);
}

int	merge_tokens(t_command *cmd, int pos)
{
	char	**result;
	char	**new_tokens;
	int		new_toks_size;
	int		i;

	new_tokens = ft_split_no_quotes(cmd->tokens[pos], ' ');
	new_toks_size = ft_strstrlen(new_tokens);
	if (!tokens_created(new_tokens, new_toks_size))
		return (-1);
	result = calloc(ft_strstrlen(cmd->tokens) + new_toks_size, sizeof(char *));
	i = -1;
	while (++i < pos)
		result[i] = cmd->tokens[i];
	i = -1;
	while (++i < new_toks_size)
		result[pos + i] = new_tokens[i];
	i = pos - 1 + i;
	free(cmd->tokens[pos]);
	while (++pos < ft_strstrlen(cmd->tokens) && ++i)
		result[i] = cmd->tokens[pos];
	free(new_tokens);
	free(cmd->tokens);
	cmd->tokens = result;
	return (new_toks_size);
}
