/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karisti- <karisti-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 19:00:46 by karisti-          #+#    #+#             */
/*   Updated: 2022/02/22 18:16:38 by karisti-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	if (argc != 1 || argv[1])
	{
		printf("Error: No arguments needed\n");
		return (0);
	}
	init_shell(&shell, env);
	while (1)
	{
		config_sig(&shell.sa, sig_handle, SIGINT);
		config_sig(&shell.sa, sig_handle, SIGQUIT);
		display_prompt(&shell);
	}
	return (0);
}
