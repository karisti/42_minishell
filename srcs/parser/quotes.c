/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:32:57 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/17 21:22:46 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Closed quotes are removed from the string
*/
void	takeout_quotes(char **str, int start, int end)
{
	int		len;
	char	*result;
	char	*aux;

	len = ft_strlen(*str);
	aux = *str;
	result = ft_strjoin_free(ft_substr(*str, 0, start),
			ft_substr(*str, start + 1, end - start - 1));
	if (len - 1 > end)
		result = ft_strjoin_free(result, ft_substr(*str, end + 1, len - end));
	*str = result;
	free(aux);
}

/*
	- If there are closed quotes, it removes them.
	- If there are unclosed quotes, prints error.

	If something is wrong, 0 is returned. Else 1
*/
int	manage_quotes(t_shell *shell, char **str)
{
	int		i;
	int		end;
	char	c;

	i = -1;
	while ((*str)[++i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			c = (*str)[i];
			end = i + 1;
			while ((*str)[end] && (*str)[end] != c)
				end++;
			if ((*str)[end] != c)
			{
				printf("minishell: %s: Unclosed quotes error\n",
					shell->line_str);
				return (0);
			}
			takeout_quotes(str, i, end);
			i = end - 2;
		}
	}
	return (1);
}
