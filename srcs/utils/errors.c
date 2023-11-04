/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 13:08:25 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/17 17:39:05 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	put_error(int errornum, char *errormsg, int ret)
{
	char	*str;
	int		msglen;

	msglen = ft_strlen(errormsg);
	if (msglen > 0)
	{
		str = ft_strjoin("minishell: ", errormsg);
		ft_putstr_fd(str, 1);
		free(str);
	}
	if (msglen > 0)
		ft_putendl_fd("", 1);
	g_exit_status = errornum;
	return (ret);
}
