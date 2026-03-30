/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:21:16 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 15:45:05 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_free(split[i]);
		i++;
	}
	ft_free(split);
}

void	free_redir(t_redir *redir)
{
	t_redir	*current;
	t_redir	*tmp;

	current = redir;
	while (current)
	{
		tmp = current;
		current = current->next;
		if (tmp->heredoc_fd != -1)
			close(tmp->heredoc_fd);
		ft_free(tmp->file);
		ft_free(tmp);
	}
}

void	free_cmd(t_cmd *pipe)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = pipe;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->args != NULL)
			free_split(tmp->args);
		if (tmp->redir != NULL)
			free_redir(tmp->redir);
		if (tmp != NULL)
			free(tmp);
	}
}

void	print_cmd_util(t_cmd *pipes)
{
	int		i;
	t_redir	*next;

	i = 0;
	ft_printf("Pipe_struct :\n\n");
	if (pipes->args && pipes->args[0])
		ft_printf("Cmd : %s\n", pipes->args[i++]);
	else
		ft_printf("Cmd : (null)0\n");
	while (pipes->args && pipes->args[i] != NULL)
		ft_printf("Cmd ARGS : %s\n", pipes->args[i++]);
	ft_printf("\nRedirections :\n");
	next = pipes->redir;
	if (!next)
		printf("Redirections : (null)\n");
	while (next)
	{
		ft_printf("Redirection type:%d file:%s\n", next->type, next->file);
		next = next->next;
	}
	ft_printf("\n");
}

void	print_cmd(t_cmd *pipes)
{
	t_cmd	*current;

	current = pipes;
	while (current)
	{
		print_cmd_util(current);
		current = current->next;
	}
}
