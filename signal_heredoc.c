/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 03:10:00 by aymen             #+#    #+#             */
/*   Updated: 2026/03/30 03:10:00 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_shell.heredoc_interrupted = 1;
	g_shell.signumber = 130;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	signal_heredoc(void)
{
	g_shell.heredoc_interrupted = 0;
	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

int	heredoc_interrupted(void)
{
	return (g_shell.heredoc_interrupted != 0);
}
