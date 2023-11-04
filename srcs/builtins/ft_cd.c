/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 22:48:29 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/22 18:43:26 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_shell *shell)
{
	char	path[1024];
	char	*update;

	update = ft_strjoin("OLDPWD=", get_env_value(shell, "PWD"));
	update_env(shell, update);
	free(update);
	if (getcwd(path, 1024))
	{
		update = ft_strjoin("PWD=", path);
		update_env(shell, update);
		free(update);
	}
}

void	ft_cd(t_shell *shell, t_command *command)
{
	char	*dest;

	if (command->argv == NULL || ft_strcmp(command->argv->content, "~") == 0)
		dest = get_env_value(shell, "HOME");
	else if (ft_strcmp(command->argv->content, "-") == 0)
		dest = get_env_value(shell, "OLDPWD");
	else if (ft_strcmp(command->argv->content, "~+") == 0)
		dest = get_env_value(shell, "PWD");
	else
		dest = command->argv->content;
	if (chdir(dest) == -1)
	{
		perror("minishell: cd");
		put_error(1, "", -42);
	}
	update_pwd(shell);
	if (command->argv != NULL && ft_strcmp(command->argv->content, "-") == 0)
		printf("%s\n", get_env_value(shell, "PWD"));
}
