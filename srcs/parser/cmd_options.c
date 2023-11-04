/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 21:22:57 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/20 19:16:23 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Parses options token to 't_command' struct
*/
void	add_cmd_options(t_command *cmd, char *opts)
{
	if (ft_strlen(opts) < 2)
		return ;
	cmd->opts = ft_strjoin_free(cmd->opts,
			ft_substr(opts, 1, ft_strlen(opts) - 1));
}

int	valid_option(char *opts)
{
	int	i;

	if (opts[0] != '-')
		return (0);
	if (ft_strlen(opts) == 1)
		return (0);
	i = 0;
	while (opts[++i])
	{
		if (opts[i] != 'n')
			return (0);
	}
	return (1);
}
