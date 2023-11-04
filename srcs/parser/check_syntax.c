/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:49:47 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/17 19:48:28 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Checks syntax of shell->line.
	
	Returns 1 if OK, 0 if error
*/
int	check_syntax(t_shell *shell)
{
	char	*aux;

	aux = shell->line;
	shell->line = ft_strtrim(shell->line, " ");
	free(aux);
	if (!shell->line || shell->line[0] == '\0')
		put_error(0, "", 0);
	else if (shell->line[0] == '|'
		|| shell->line[ft_strlen(shell->line) - 1] == '|')
		put_error(0, "syntax error", 0);
	else
		return (1);
	return (0);
}
