/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 15:11:44 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/21 17:52:00 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*put_value(t_shell *shell, char *key)
{
	char	*env_value;
	char	*line1;

	line1 = NULL;
	env_value = get_env_value(shell, key);
	if (env_value)
	{
		if (ft_strcmp(key, "?") == 0)
			line1 = env_value;
		else
			line1 = ft_strdup(env_value);
	}
	if (!line1)
		line1 = ft_strdup("");
	return (line1);
}

/*
	Replaces environment variable key in 'shell->line'
	by its value.
	The position after value is returned.
*/
int	replace_key_with_value(t_shell *shell, char **token, int lim[2], char *key)
{
	char	*line[3];
	int		ret;

	ret = 0;
	line[0] = ft_substr((*token), 0, lim[0] - 1);
	line[2] = ft_substr((*token), lim[1], ft_strlen((*token)) - 1);
	line[1] = put_value(shell, key);
	free((*token));
	if (lim[0] - 1 > 0)
	{
		(*token) = ft_strjoin_free(line[0], line[1]);
		ret = ft_strlen((*token)) - 1;
	}
	else
	{
		free(line[0]);
		(*token) = line[1];
	}
	(*token) = ft_strjoin_free((*token), line[2]);
	return (ret);
}

/*
	Gets environment variable key from 'shell->line'
	when '$' is detected
*/
int	parse_key(t_shell *shell, char **token, int i, int dquote)
{
	int		lim[2];
	char	*env_key;

	lim[1] = ++i;
	lim[0] = i;
	if (!(*token)[lim[1]] || (!ft_isalnum((*token)[lim[1]])
			&& !ft_strchr("_?'\"$", (*token)[lim[1]])))
		return (lim[1]);
	while (ft_isalnum((*token)[lim[1]]) || (*token)[lim[1]] == '_'
		|| (lim[1] == i && !ft_isalpha((*token)[lim[1]])))
	{
		if (lim[1] == i && !ft_isalpha((*token)[i]) && (*token)[lim[1]] != '_')
		{
			if (((*token)[i] == '"' && dquote % 2 == 1))
				return (lim[1]);
			if (ft_isdigit((*token)[i]) || (*token)[i] == '?')
				lim[1]++;
			break ;
		}
		lim[1]++;
	}
	env_key = ft_substr((*token), i, lim[1] - i);
	i = replace_key_with_value(shell, token, lim, env_key);
	free(env_key);
	return (i);
}

void	expand_envs(t_shell *shell, char **token)
{
	int			i;
	int			dquote;
	int			squote;

	i = 0;
	dquote = 0;
	squote = 0;
	while ((*token)[i] != '\0')
	{
		while ((*token)[i] != '\0' && (*token)[i] != '$')
		{
			if ((*token)[i] == '\'' && dquote % 2 == 0)
				squote++;
			if ((*token)[i] == '"' && squote % 2 == 0)
				dquote++;
			i++;
		}
		if ((*token)[i] == '$' && (squote == 0 || squote % 2 == 0))
			i = parse_key(shell, token, i, dquote);
		else if ((*token)[i] == '$')
			i++;
	}
}
