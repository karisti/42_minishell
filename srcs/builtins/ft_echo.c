/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 21:35:41 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/07 23:11:16 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(t_command *command)
{
	t_list	*aux;

	aux = command->argv;
	while (aux)
	{
		if (ft_strlen((char *)aux->content) > 0)
			printf("%s", (char *)aux->content);
		if (aux->next)
			printf(" ");
		aux = aux->next;
	}
	if (command->opts && ft_strchr(command->opts, 'n') != NULL)
		return ;
	printf("\n");
}
