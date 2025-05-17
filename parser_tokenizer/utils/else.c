/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:21:16 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 06:28:11 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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
		free(tmp->file);
		free(tmp);
	}
}

void	free_cmd(t_cmd *pipe)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = pipe;
	while (current)
	{
		tmp = current;
		current = current->next;
		free_split(tmp->args);
		free_redir(tmp->redir);
		free(tmp);
	}
}

void	print_cmd_util(t_cmd *pipes)
{
	int		i;
	t_redir	*next;

	i = 0;
	ft_printf("Pipe_struct :\n\n");
	ft_printf("Cmd : %s\n", (pipes->args[i++]));
	while ((pipes->args)[i] != NULL)
		ft_printf("Cmd ARGS : %s\n", (pipes->args[i++]));
	ft_printf("\nRedirections :\n");
	next = (pipes->redir);
	while (next)
	{
		if (next->type == T_REDIR_IN)
			ft_printf("Redirection type : REDIR_IN ");
		if (next->type == T_REDIR_OUT)
			ft_printf("Redirection type : REDIR_OUT ");
		if (next->type == T_REDIR_APPEND)
			ft_printf("Redirection type : REDIR_APPEND ");
		if (next->type == T_HEREDOC)
			ft_printf("Redirection type : HEREDOC ");
		ft_printf("Redirection file : %s\n", next->file);
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
