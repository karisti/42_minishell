/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:01:29 by karisti-          #+#    #+#             */
/*   Updated: 2022/01/26 17:41:16 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Modified strjoin, it frees s1 and s2
	before returning the result
*/
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_newstr(size);
	while (i < size && ptr)
	{
		if (i < (size - ft_strlen(s2)))
			ptr[i] = s1[i];
		else
		{
			ptr[i] = s2[j];
			j++;
		}
		i++;
	}
	free(s1);
	free(s2);
	return (ptr);
}
