/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:23:27 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 06:25:42 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*init_pipes(t_token *lst)
{
	t_cmd	*pipes;

	if (!lst)
		return (NULL);
	pipes = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pipes)
		return (NULL);
	pipes->args = NULL;
	pipes->redir = NULL;
	pipes->next = NULL;
	return (pipes);
}

int	token_count(t_token *lst)
{
	t_token	*current;
	int		i;

	if (!lst)
		return (0);
	i = 0;
	current = lst;
	while (current)
	{
		if (current->type == T_CMD || current->type == T_ARG)
			i++;
		current = current->next;
	}
	return (i);
}

t_cmd	*parse_tokens(t_token *lst)
{
	t_token	*current;
	t_redir	*next;
	t_cmd	*pipes;

	pipes = init_pipes(lst);
	if (!pipes)
		return (NULL);
	if (set_args(pipes, lst) == 0)
		return (NULL);
	current = lst;
	next = NULL;
	cmd_set_redir(pipes, &current, &next);
	return (pipes);
}
