/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 19:03:47 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/18 21:26:56 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(t_shell *shell, t_command *command, int is_fork)
{
	close(command->pipe.w);
	restore_io(shell->saved_std);
	if (!is_fork)
		printf("exit\n");
	if (command->argc > 0)
	{
		if (!str_is_number(command->argv->content))
		{
			g_exit_status = 255;
			printf("minishell: exit: numeric argument required\n");
		}
		else
		{
			g_exit_status = ft_atoi((char *)command->argv->content);
			if (command->argc > 1)
			{
				printf("minishell: exit: too many arguments\n");
				return ;
			}
		}
	}
	end_prompt(shell);
}
