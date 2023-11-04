/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:12:43 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/22 18:16:22 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	display_prompt(t_shell *shell)
{
	shell->line = readline("minishell: ");
	if (!shell->line)
	{
		put_error(0, "exit", 0);
		end_prompt(shell);
	}
	if (ft_strlen(shell->line) > 0)
		add_history(shell->line);
	if (!check_syntax(shell))
		return (free_shell(shell, 0));
	shell->line_str = ft_strdup(shell->line);
	if (!parse(shell, -1))
	{
		reset_shell(shell);
		return (0);
	}
	executor(shell);
	reset_shell(shell);
	return (1);
}

void	free_env(void *env)
{
	char	**env_sp;

	env_sp = env;
	free(env_sp[0]);
	free(env_sp[1]);
	free(env_sp);
}

void	end_prompt(t_shell *shell)
{
	free_shell(shell, 0);
	ft_lstclear(&shell->env_list, (void *)free_env);
	clear_history();
	exit(g_exit_status);
}
