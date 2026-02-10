/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 20:39:49 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"
#include "../../minishell.h"

char **dup_tab(char **tab)
{
    int i, count;
    char **new_tab;

    if (!tab)
        return NULL;

    // Compter le nombre d'éléments
    count = 0;
    while (tab[count])
        count++;

    // Allouer le tableau de pointeurs +1 pour le NULL final
    new_tab = malloc(sizeof(char *) * (count + 1));
    if (!new_tab)
        return NULL;

    // Dupliquer chaque string
    i = 0;
    while (i < count)
    {
        new_tab[i] = strdup(tab[i]);
        if (!new_tab[i])
        {
            // en cas d'échec, free déjà alloué
            while (--i >= 0)
                free(new_tab[i]);
            free(new_tab);
            return NULL;
        }
        i++;
    }
    new_tab[i] = NULL; // terminer par NULL
    return new_tab;
}

void	set_fd(t_cmd *pipes)
{
	t_redir	*current;
	int	fd1;

	current = pipes->redir;
	while (current)
	{
		if (current->type == T_REDIR_IN)
		{
			fd1 = open(current->file, O_RDONLY, 0644);
			if (fd1 == -1)
			{
				perror(current->file);
				free_cmd(pipes);
				exit(1);
			}
			if (dup2(fd1, STDIN_FILENO) == -1)
			{
				close(fd1);
				free_cmd(pipes);
				exit(EXIT_FAILURE);
			}
			close(fd1);
		}
		else if (current->type == T_REDIR_OUT)
		{
			fd1 = open(current->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd1 == -1)
			{
				perror(current->file);
				free_cmd(pipes);
				exit(1);
			}
			if (dup2(fd1, STDOUT_FILENO) == -1)
			{
				close(fd1);
				free_cmd(pipes);
				exit(EXIT_FAILURE);
			}
			close(fd1);
		}
		current = current->next;
	}
}

void	child1(t_cmd *pipes, char **env)
{
	set_fd(pipes);
	if (pipes->args[0])
	{
		commande(env, pipes, pipes);
	}
	else
	{
		free_cmd(pipes);
		exit(0);
	}
}

int	pipex(t_cmd *pipes, char **env)
{
	int		pipefd[2];
	pid_t	pid;
	t_cmd	*current;
	int		prev_pipe;

	if (!pipes)
		return (1);
	current = pipes;
	if (current->next != NULL)
	{
		printf("\n\nCHECK\n\n");
		current = pipes;
		prev_pipe = -1;
		while (current)
		{
			if (current->next && pipe(pipefd) == -1)
			{
				perror("pipe");
				return (1);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				return (1);
			}
			if (pid == 0)
			{
				t_redir *r = current->redir;
				int in_handled = 0, out_handled = 0;

				while (r)
				{
					int fd;
					if (r->type == T_REDIR_IN)
					{
						fd = open(r->file, O_RDONLY);
						if (fd == -1)
						{
							perror(r->file);
							free_cmd(current);
							exit(1);
						}
						dup2(fd, STDIN_FILENO);
						close(fd);
						in_handled = 1;
					}
					else if (r->type == T_REDIR_OUT)
					{
						fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						if (fd == -1)
						{
							perror(r->file);
							free_cmd(current);
							exit(1);
						}
						dup2(fd, STDOUT_FILENO);
						close(fd);
						out_handled = 1;
					}
					r = r->next;
				}
				if (!in_handled && prev_pipe != -1)
					dup2(prev_pipe, STDIN_FILENO);
				if (!out_handled && current->next)
					dup2(pipefd[1], STDOUT_FILENO);

				if (prev_pipe != -1)
					close(prev_pipe);
				if (current->next)
				{
					close(pipefd[0]);
					close(pipefd[1]);
				}
				//free_cmd(pipes);
				commande(env, pipes, current);
				exit(1);
			}
			if (prev_pipe != -1)
				close(prev_pipe);
			if (current->next)
			{
				close(pipefd[1]);
				prev_pipe = pipefd[0];
			}
			current = current->next;
		}
		while (wait(NULL) != -1);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			child1(pipes, env);

		if (pid == -1)
			return (-1);
		wait(NULL);
	}
	return (0);
}

