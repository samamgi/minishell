/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:27:26 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 06:27:47 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parse_all_util2(t_token **tmp, t_token **current)
{
	while ((*current) && (*current)->type != T_PIPE)
		(*current) = (*current)->next;
	if ((*current))
	{
		(*tmp) = (*current)->next;
		(*current)->next = NULL;
	}
	else
		(*tmp) = NULL;
}

void	parse_all_util(t_cmd **pipes, t_token **tmp, t_token **start,
		t_token **current)
{
	t_cmd	*last;

	last = NULL;
	while ((*current))
	{
		parse_all_util2(tmp, current);
		if (!(*pipes))
		{
			*pipes = parse_tokens(*start);
			printf("pipes addr apres malloc %p\n", pipes);
			last = *pipes;
		}
		else
		{
			last->next = parse_tokens(*start);
			last = last->next;
		}
		if ((*current))
			(*current)->next = (*tmp);
		(*start) = (*tmp);
		(*current) = (*tmp);
	}
}

t_cmd	*parse_all(t_token *lst)
{
	t_cmd	*pipes;
	t_token	*tmp;
	t_token	*start;
	t_token	*current;

	start = lst;
	current = lst;
	pipes = NULL;
	tmp = NULL;
	parse_all_util(&pipes, &tmp, &start, &current);
	//print_cmd(pipes);
	token_clear(lst);
	return (pipes);
}
