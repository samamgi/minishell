/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 23:54:49 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 15:32:21 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child1(int fd1, int pipefd[2], char **av, t_cmd *pipes, char **env)
{
	close(pipefd[0]);
	fd1 = open(pipes->redir->file, O_RDONLY, 0644);
	if (fd1 == -1)
	{
		close(pipefd[1]);
		perror(pipes->redir->file);
		exit(1);
	}
	if (dup2(fd1, STDIN_FILENO) == -1)
	{
		close(fd1);
		exit(EXIT_FAILURE);
	}
	close(fd1);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	commande(av, env);
}

void	child2(int fd2, int pipefd[2], char **av, t_cmd *pipes, char **env)
{
	close(pipefd[1]);
	fd2 = open(pipes->redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 == -1)
	{
		close(pipefd[0]);
		perror(pipes->redir->file);
		exit(EXIT_FAILURE);
	}
	if (dup2(fd2, STDOUT_FILENO) == -1)
	{
		close(fd2);
		exit(EXIT_FAILURE);
	}
	close(fd2);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	commande(av, env);
}

int	pipex(t_cmd *pipes, char **env)
{
	int		fd1;
	int		fd2;
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (1);
	fd1 = -1;
	fd2 = -1;
	pid = fork();
	if (pid == 0)
		child1(fd1, pipefd, pipes->args, pipes, env);
	if (pid == -1)
		return (close(pipefd[0]), close(pipefd[1]), -1);
	//pipes = pipes->next;
	if (pipes != NULL)
	{
		pid = fork();
		if (pid == 0)
			child2(fd2, pipefd, pipes->args, pipes, env);
		if (pid == -1)
			return (close(pipefd[0]), close(pipefd[1]), -1);
	}
	close(pipefd[1]);
	close(pipefd[0]);
	if (fd1 == -1)
		wait(NULL);
	wait(NULL);
	return (0);
}
