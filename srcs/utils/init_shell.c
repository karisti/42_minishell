/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:34:24 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/20 15:52:18 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_shlvl(t_shell *shell)
{
	char	*env_val;
	char	*update;
	int		value;

	env_val = get_env_value(shell, "SHLVL");
	if (env_val == NULL || !str_is_number(env_val))
		value = 1;
	else
	{
		value = ft_atoi(env_val);
		value++;
	}
	update = ft_strjoin_free(ft_strdup("SHLVL="), ft_itoa(value));
	update_env(shell, update);
	free(update);
}

/*
	We initialize the list 'shell->env_list'
	with current system values
*/
void	init_envs_list(t_shell *shell, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_lstadd_back(&shell->env_list, ft_lstnew(ft_split(env[i], '=')));
}

/*
	Initialize 't_shell' structure
*/
void	init_shell(t_shell *shell, char **env)
{
	g_exit_status = 0;
	shell->line = NULL;
	shell->line_str = NULL;
	shell->env = env;
	shell->env_list = NULL;
	shell->cmd_table = NULL;
	shell->cmd_count = 0;
	shell->saved_std[0] = dup(READ_END);
	shell->saved_std[1] = dup(WRITE_END);
	init_envs_list(shell, env);
	update_shlvl(shell);
}

void	reset_shell(t_shell *shell)
{
	shell->cmd_count = 0;
	free_shell(shell, 0);
	shell->line = NULL;
}

int	free_shell(t_shell *shell, int ret)
{
	char	*aux;

	ft_lstclear(&shell->cmd_table, (void *)free_command);
	if (shell->line_str)
	{
		aux = shell->line_str;
		shell->line_str = NULL;
		free(aux);
	}
	if (shell->line)
		free(shell->line);
	return (ret);
}
