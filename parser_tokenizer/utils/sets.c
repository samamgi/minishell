/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:26:21 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 06:27:13 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_redir	*set_redir(t_token_type token, char *value)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = token;
	new->file = ft_strdup(value);
	new->next = NULL;
	return (new);
}

int	set_args(t_cmd *pipes, t_token *lst)
{
	t_token	*current;
	int		i;

	current = lst;
	i = token_count(lst);
	pipes->args = (char **)malloc(sizeof(char *) * (i + 1));
	if (!(pipes->args))
		return (0);
	(pipes->args)[i] = NULL;
	i = 0;
	while (current)
	{
		if (current->type == T_CMD || current->type == T_ARG)
		{
			(pipes->args)[i] = ft_strdup(current->value);
			if (!(pipes->args)[i])
				return (0);
			i++;
		}
		current = current->next;
	}
	return (1);
}

void	cmd_set_redir(t_cmd *pipes, t_token **current, t_redir **next)
{
	while ((*current))
	{
		if ((*current) && ((*current)->type == T_REDIR_IN
				|| (*current)->type == T_REDIR_OUT
				|| (*current)->type == T_REDIR_APPEND
				|| (*current)->type == T_HEREDOC))
		{
			if ((pipes->redir) == NULL)
			{
				(pipes->redir) = set_redir((*current)->type, (*current)->value);
				(*next) = (pipes->redir);
				(*current) = (*current)->next;
			}
			else
			{
				(*next)->next = set_redir((*current)->type, (*current)->value);
				(*next) = (*next)->next;
				(*current) = (*current)->next;
			}
		}
		else
			(*current) = (*current)->next;
	}
	pipes->next = NULL;
}
