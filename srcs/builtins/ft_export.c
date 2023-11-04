/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 20:50:06 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/12 12:40:39 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_stack(t_list **src, t_list **dst)
{
	t_list	*source;

	source = *src;
	while (source)
	{
		ft_lstadd_back(&(*dst), ft_lstnew(source->content));
		source = source->next;
	}
}

void	ft_sortlist(t_list *env_list)
{
	t_list	*envs;
	t_list	*iter;
	t_list	*tmp;

	iter = NULL;
	copy_stack(&env_list, &iter);
	envs = iter;
	while (envs != NULL)
	{
		tmp = NULL;
		while (iter)
		{
			if (tmp == NULL || (ft_strcmp(((char **)iter->content)[0],
					((char **)tmp->content)[0])) < 0)
				tmp = iter;
			iter = iter->next;
		}
		printf("declare -x %s=\"%s\"\n",
			((char **)tmp->content)[0], ((char **)tmp->content)[1]);
		iter = envs;
		ft_lstrem(&iter, tmp->content);
		envs = iter;
	}
}

void	ft_export(t_shell *shell, t_command *command)
{
	t_list	*argv;

	argv = command->argv;
	if (argv == NULL)
		ft_sortlist(shell->env_list);
	while (argv)
	{
		update_env(shell, (char *)argv->content);
		argv = argv->next;
	}
}
