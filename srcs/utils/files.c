/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 10:30:05 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/17 17:40:29 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(char *path, int mode)
{
	char	cwd[256];
	int		file;
	char	*error;

	file = -1;
	if (!getcwd(cwd, sizeof(cwd)))
		return (-1);
	file = open(path, mode, 0644);
	if (file == -1)
	{
		error = ft_strjoin("minishell: ", path);
		perror(error);
		free(error);
		return (put_error(1, "", -1));
	}
	return (file);
}

int	check_file(char *path)
{
	int			fd;
	struct stat	st;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		fstat(fd, &st);
		if (st.st_mode & S_IXUSR)
		{
			close(fd);
			return (1);
		}
		close(fd);
	}
	return (0);
}
