/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:42:53 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/21 11:22:17 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strstrlen(char **str)
{
	int	j;

	j = 0;
	if (!str)
		return (0);
	while (str[j])
		j++;
	return (j);
}
