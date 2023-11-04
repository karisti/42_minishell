/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:29:51 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/21 12:02:41 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_unset(t_shell *shell, t_command *command)
{
	t_list	*argvs;
	char	*env;

	argvs = command->argv;
	if (!argvs)
		printf("unset: not enough arguments\n");
	while (argvs)
	{
		env = (char *)argvs->content;
		if ((env && !ft_isalpha(env[0]) && env[0] != '_')
			|| (ft_strlen(env) == 0 || !ft_isalnum_underscore(env)))
			put_error(1, "Not a valid identifier", 0);
		else
			del_from_env_list(shell, (char *)argvs->content);
		argvs = argvs->next;
	}
}
