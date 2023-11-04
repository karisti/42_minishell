/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_no_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 19:09:00 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/17 17:50:06 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	Counts words taking into account simple
	and double quotes
*/
static size_t	count_words_no_quotes(char *s, char c)
{
	size_t		nb_words;
	int			dquote;
	int			squote;

	dquote = 0;
	squote = 0;
	nb_words = 1;
	while (*s)
	{
		if (*s == '\'' && dquote % 2 == 0)
			squote++;
		if (*s == '"' && squote % 2 == 0)
			dquote++;
		if (squote % 2 == 0 && dquote % 2 == 0)
			if (*s == c && s[1] && s[1] != c)
				++nb_words;
		++s;
	}
	return (nb_words);
}

char	**ft_split_no_quotes_1(char const *s, char c,
	char **result, size_t nb_words)
{
	char		*wrd;
	int			dquote;
	int			squote;

	dquote = 0;
	squote = 0;
	wrd = (char *)s;
	while (*s)
	{
		if (*s == '\'' && dquote % 2 == 0)
			squote++;
		if (*s == '"' && squote % 2 == 0)
			dquote++;
		if (squote % 2 == 0 && dquote % 2 == 0 && *s == c)
		{
			if (wrd != s)
				*(result++) = ft_substr(wrd, 0, s - wrd);
			wrd = (char *)s + 1;
		}
		++s;
	}
	if (wrd != s)
		*(result++) = ft_substr(wrd, 0, s - wrd);
	*result = NULL;
	return (result - nb_words);
}

/*
	Modified split, it takes into account simple
	and double quotes, avoiding split inside
	quotes
*/
char	**ft_split_no_quotes(char const *s, char c)
{
	size_t		nb_words;
	char		**result;

	nb_words = count_words_no_quotes((char *)s, c);
	result = (char **)malloc(sizeof(char *) * (nb_words + 1));
	if (!result)
		return (NULL);
	return (ft_split_no_quotes_1(s, c, result, nb_words));
}
