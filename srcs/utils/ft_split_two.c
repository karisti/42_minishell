/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:33:05 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/19 00:54:15 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_split_two(char *str, char c)
{
	char	**result;
	int		i;

	result = (char **)ft_calloc(3, sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
	{
		result[0] = ft_substr(str, 0, i);
		result[1] = ft_substr(str, i + 1, ft_strlen(str) - i - 1);
	}
	else
	{
		free(result);
		return (NULL);
	}
	return (result);
}
