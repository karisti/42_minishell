/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpernas- <gpernas-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:24:06 by gpernas-          #+#    #+#             */
/*   Updated: 2022/02/21 17:22:37 by gpernas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handle_fork(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_exit_status = 131;
	}
}

void	sig_handle_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		exit(130);
	}
}

void	sig_handle(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 130;
	}
	else if (signum == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	config_sig(struct sigaction *sa, void (*handler) (int), int sig)
{
	sa->sa_handler = handler;
	sa->sa_flags = 0;
	sigaction(sig, sa, NULL);
}
