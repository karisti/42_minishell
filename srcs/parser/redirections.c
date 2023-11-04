/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:10:12 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/21 15:29:29 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Check if token is redirection
*/
int	is_redirection(char *str)
{
	if (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<<") == 0 || ft_strcmp(str, "<") == 0)
		return (1);
	return (0);
}

/*
	Parse redirections from str to 't_redir' struct
*/
int	get_redirections(t_shell *shell, t_command *cmd, char **array, int i)
{
	t_redir		*redir;
	int			i1;

	redir = new_redir();
	if (!redir)
		return (-42);
	i1 = i;
	if (ft_strcmp(array[i1], ">>") == 0 || ft_strcmp(array[i1], "<<") == 0)
		redir->append = 1;
	if (ft_strcmp(array[i1], "<") == 0)
		redir->is_input = 1;
	if (ft_strcmp(array[i1], ">>") == 0 || ft_strcmp(array[i1], ">") == 0
		|| ft_strcmp(array[i1], "<") == 0)
	{
		redir->str = ft_strdup(array[++i1]);
		ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	}
	else if (ft_strcmp(array[i1], "<<") == 0)
	{
		if (!display_heredoc(shell, cmd, redir, array[++i1]))
			return (-42);
	}
	return (i1 - i);
}

/*
	Adds space befor and/or after 'i' position
	in 'str'
*/
char	*add_spaces(char *str, int i, int prev, int post)
{
	char	*new_str;
	char	*pos_str;
	char	*post_str;

	new_str = ft_substr(str, 0, i);
	pos_str = ft_substr(str, i, 1);
	post_str = ft_substr(str, i + 1, ft_strlen(str) - i);
	free(str);
	if (prev)
		new_str = ft_strjoin_free(new_str, ft_strdup(" "));
	new_str = ft_strjoin_free(new_str, pos_str);
	if (post)
		new_str = ft_strjoin_free(new_str, ft_strdup(" "));
	new_str = ft_strjoin_free(new_str, post_str);
	return (new_str);
}

/*
	Adds spaces before and after redirection characters
	to avoid problems when spliting

	Returns same char * with spaces before and after
	redirection signs
*/

int	fix_redirs(char **s, unsigned long i, int dquote, int squote)
{
	char			*str;
	unsigned long	prev;
	unsigned long	post;

	str = *s;
	prev = 0;
	post = 0;
	if (i > 0 && squote % 2 == 0 && dquote % 2 == 0 && str[i - 1] != ' '
		&& ((str[i] == '>' && str[i - 1] != '>') || (str[i] == '<'
				&& str[i - 1] != '<')))
		prev = 1;
	if (i < ft_strlen(str) - 1 && squote % 2 == 0 && dquote % 2 == 0
		&& str[i + 1] != ' ' && ((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<')))
		post = 1;
	if (prev || post)
	{
		*s = add_spaces(str, i, prev, post);
		i = i + prev + post;
	}
	return (i);
}

char	*fix_redirection_spaces(char *str)
{
	unsigned long	i;
	int				dquote;
	int				squote;

	dquote = 0;
	squote = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' && dquote % 2 == 0)
			squote++;
		if (str[i] == '"' && squote % 2 == 0)
			dquote++;
		i = fix_redirs(&str, i, dquote, squote);
	}
	return (str);
}
