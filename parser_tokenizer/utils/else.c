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

// void free_cmd(t_cmd *cmd)
// {
//     t_cmd *tmp;
//     while (cmd)
//     {
//         tmp = cmd;
//         if (cmd->args)
//             free(cmd->args);
//         if (cmd->args)
//             free_split(cmd->args);
//         if (cmd->redir)
//             free_redir(cmd->redir); // 🔥 toujours appeler, même si commande == NULL
//         cmd = cmd->next;
//         free(tmp);
//     }
// }

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
	if (!(pipes->args) || !(pipes->args)[0])
		ft_printf("Cmd : (null)0\n");
	else
	{
		ft_printf("Cmd : %s\n", pipes->args[i++]); // première commande
		while (pipes->args[i] != NULL)
			ft_printf("Cmd ARGS : %s\n", pipes->args[i++]); // les arguments
	}
	ft_printf("\nRedirections :\n");
	next = (pipes->redir);
	if (!next)
		printf("Redirections : (null)\n");
	else
	{
		while (next)
		{
			if (next->type == T_REDIR_IN)
				ft_printf("Redirection type : REDIR_IN ");
			else if (next->type == T_REDIR_OUT)
				ft_printf("Redirection type : REDIR_OUT ");
			else if (next->type == T_REDIR_APPEND)
				ft_printf("Redirection type : REDIR_APPEND ");
			else if (next->type == T_HEREDOC)
				ft_printf("Redirection type : HEREDOC ");
			ft_printf("Redirection file : %s\n", next->file);
			next = next->next;
		}
	}
	ft_printf("\n");
}

// void	print_cmd_util(t_cmd *pipes)
// {
// 	int		i;
// 	t_redir	*next;

// 	i = 0;
// 	ft_printf("Pipe_struct :\n\n");
// 	if (!(pipes->args))
// 		ft_printf("Cmd : (null)\n");
// 	else
// 	{
// 		ft_printf("Cmd : %s0\n", (pipes->args[i++]));
// 		while ((pipes->args)[i] != NULL)
// 			ft_printf("Cmd ARGS : %s\n", (pipes->args[i++]));
// 	}
// 	ft_printf("\nRedirections :\n");
// 	next = (pipes->redir);
// 	if (!next)
// 		printf("Redirections : (null)\n");
// 	else
// 	{
// 		while (next)
// 		{
// 			if (next->type == T_REDIR_IN)
// 				ft_printf("Redirection type : REDIR_IN ");
// 			if (next->type == T_REDIR_OUT)
// 				ft_printf("Redirection type : REDIR_OUT ");
// 			if (next->type == T_REDIR_APPEND)
// 				ft_printf("Redirection type : REDIR_APPEND ");
// 			if (next->type == T_HEREDOC)
// 				ft_printf("Redirection type : HEREDOC ");
// 			ft_printf("Redirection file : %s0\n", next->file);
// 			next = next->next;
// 		}
// 	}
// 	ft_printf("\n");
// }

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
