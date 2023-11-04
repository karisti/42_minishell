/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:08:01 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/21 19:09:50 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_command(t_shell *shell, t_command *command)
{
	char	**path;
	int		i;
	char	*path_val;

	i = 0;
	if (check_file(command->cmd))
		return (command->cmd);
	path_val = get_env_value(shell, "PATH");
	path = ft_split(path_val, ':');
	while (path_val && path[i])
	{
		command->cmd_path = ft_strjoin_free(path[i], ft_strdup("/"));
		command->cmd_path = ft_strjoin_free(command->cmd_path,
				ft_strdup(command->cmd));
		if (check_file(command->cmd_path) && i++)
			break ;
		i++;
	}
	if (!path_val || path[i - 1] == NULL)
		return (NULL);
	while (path[i])
		free(path[i++]);
	free(path);
	return (command->cmd_path);
}

char	**get_argv(t_command *command)
{
	t_list	*argv_list;
	char	**argv;
	int		i;

	argv_list = command->argv;
	argv = ft_calloc(ft_lstsize(argv_list) + 3, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	argv[i] = ft_strdup(command->cmd);
	if (ft_strlen(command->opts) > 0)
		argv[++i] = ft_strjoin("-", ft_strdup(command->opts));
	while (argv_list)
	{
		argv[++i] = ft_strdup((char *)argv_list->content);
		argv_list = argv_list->next;
	}
	return (argv);
}

void	restore_io(int saved_std[2])
{
	dup2(saved_std[0], STDIN_FILENO);
	dup2(saved_std[1], STDOUT_FILENO);
}

void	execute_execve(t_shell *shell, t_command *command)
{
	if (!command->cmd)
		return ;
	update_envs_str(shell, shell->env_list);
	if (execve(get_path_command(shell, command),
			get_argv(command), shell->env) == -1)
	{
		restore_io(shell->saved_std);
		printf("minishell: %s: command not found\n", command->cmd);
		put_error(127, "", 127);
	}
}

void	execute_builtins(t_shell *shell, t_command *command, int is_fork)
{
	redirect_pipe(command);
	if (!apply_redirections_std(command))
	{
		if (is_fork)
			exit(1);
		return ;
	}
	if (ft_strcmp(command->cmd, "cd") == 0)
		ft_cd(shell, command);
	else if (ft_strcmp(command->cmd, "echo") == 0)
		ft_echo(command);
	else if (ft_strcmp(command->cmd, "export") == 0)
		ft_export(shell, command);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		ft_unset(shell, command);
	else if (ft_strcmp(command->cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(command->cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(command->cmd, "exit") == 0)
		ft_exit(shell, command, is_fork);
	else
		execute_execve(shell, command);
	if (is_fork)
		exit(g_exit_status);
}
