/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:42:07 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 22:55:01 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int g_in_readline = 0;

void sigint_handle(int sig)
{
    (void)sig;
    g_signumber = 130;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    if (g_in_readline)
        rl_redisplay();
}

void setup_signal(void)
{
    signal(SIGINT, sigint_handle);
    signal(SIGQUIT, SIG_IGN);
}

void	set_readline_state(int state)
{
	g_in_readline = state;
}


void signal_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void sigint_heredoc(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    exit(130);
    
    //Si le heredoc n’est pas dans un fork, alors exit(130) tue tout ton shell, pas seulement le heredoc.
    //En bash, Ctrl+C dans un heredoc ne tue que l’input, le shell continue à tourner.
}
void signal_heredoc(void)
{
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}

/*
 faut gérer $? correctement avec waitpid
*/