/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 14:39:09 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/19 00:49:23 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Searches key in environment variable list.
	If exist, node is returned.
	If not, NULL is returned.
*/
t_list	*search_key_in_env_list(t_shell *shell, char *key)
{
	t_list	*node;

	node = shell->env_list;
	while (node)
	{
		if (ft_strcmp(((char **)node->content)[0], key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
	We get the value of the environment variable
	given as key.
		- If not found, NULL is returned.
		- If found, a copy of its value is returned.
*/
char	*get_env_value(t_shell *shell, char *key)
{
	t_list	*node;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(g_exit_status));
	node = search_key_in_env_list(shell, key);
	if (!node)
		return (NULL);
	return (((char **)node->content)[1]);
}

/*
	If environment variable exists, we update its value.
	If doesn´t exist, we add as new env.
	1 is returned if OK, 0 if there is some error.
*/
int	update_env(t_shell *shell, char *env)
{
	t_list	*node;
	char	**key_value;

	if (env && !ft_isalpha(env[0]) && env[0] != '_')
		return (put_error(1, "Not a valid identifier", 0));
	key_value = ft_split_two(env, '=');
	if (ft_strlen(env) == 0 || (key_value && (!key_value[0]
				|| !ft_isalnum_underscore(key_value[0]))))
		return (put_error(1, "Not a valid identifier", 0));
	if (!key_value || !key_value[1])
		return (put_error(0, "", 0));
	node = search_key_in_env_list(shell, key_value[0]);
	if (node)
	{
		free(((void **)node->content)[0]);
		free(((void **)node->content)[1]);
		free(node->content);
		node->content = key_value;
	}
	else
		ft_lstadd_front(&shell->env_list, ft_lstnew(key_value));
	return (1);
}

/*
	Deletes environment variable if key
	is found in de list.
*/
void	del_from_env_list(t_shell *shell, char *key)
{
	t_list	*node;
	t_list	*prev;

	node = shell->env_list;
	prev = NULL;
	while (node)
	{
		if (ft_strcmp(((char **)node->content)[0], key) == 0)
		{
			if (!prev)
				shell->env_list = shell->env_list->next;
			else
				prev->next = node->next;
			free(((char **)node->content)[0]);
			free(((char **)node->content)[1]);
			free(node->content);
			free(node);
			break ;
		}
		prev = node;
		node = node->next;
	}
}

void	update_envs_str(t_shell *shell, t_list *envs_list)
{
	t_list	*node;
	char	**envs;
	int		i;

	node = envs_list;
	envs = ft_calloc(ft_lstsize(envs_list) + 1, sizeof(char *));
	i = 0;
	while (node)
	{
		envs[i] = ft_strjoin(((char **)node->content)[0], "=");
		envs[i] = ft_strjoin_free(envs[i],
				ft_strdup(((char **)node->content)[1]));
		node = node->next;
		i++;
	}
	shell->env = envs;
}
