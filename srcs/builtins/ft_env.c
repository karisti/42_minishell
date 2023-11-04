/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:50:33 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/18 11:17:56 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_envs_list(void *node_content)
{
	printf("%s=%s\n", ((char **)node_content)[0], ((char **)node_content)[1]);
}

void	ft_env(t_shell *shell)
{
	ft_lstiter(shell->env_list, print_envs_list);
}
