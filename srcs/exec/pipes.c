/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 21:25:00 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/19 11:53:37 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_pipe(t_shell *shell, int *fd1)
{
	if (shell->cmd_count > 1)
	{
		if (pipe(fd1) != 0)
		{
			printf("Error creating pipe\n");
			return (0);
		}
	}
	return (1);
}

void	close_pipe(t_command *command)
{
	if (command->pipe.w > -1)
		close(command->pipe.w);
	if (command->pipe.r > -1)
		close(command->pipe.r);
}

void	redirect_pipe(t_command *command)
{
	if (command->pipe.w > -1)
		dup2(command->pipe.w, STDOUT_FILENO);
	if (command->pipe.r > -1)
		dup2(command->pipe.r, STDIN_FILENO);
}
