/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 05:16:34 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 15:45:21 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	operators(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	words(char c)
{
	return (!operators(c) && (!((c >= 9 && c <= 13) || c == 32)));
}

void	token_clear(t_token *lst)
{
	t_token	*current;
	t_token	*tmp;

	current = lst;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->value);
		free(tmp);
	}
}

void	print_token(t_token *lst)
{
	t_token	*current;

	if (!lst)
		return ;
	current = lst;
	while (current)
	{
		if (current->type == T_REDIR_OUT)
			ft_printf("type = REDIR_OUT\n");
		if (current->type == T_REDIR_IN)
			ft_printf("type = REDIR_IN\n");
		if (current->type == T_PIPE)
			ft_printf("type = PIPE\n");
		if (current->type == T_REDIR_APPEND)
			ft_printf("type = REDIR_APPEND\n");
		if (current->type == T_HEREDOC)
			ft_printf("type = HERE_DOC\n");
		if (current->type == T_CMD)
			ft_printf("type = CMD\n");
		if (current->type == T_ARG)
			ft_printf("type = ARG\n");
		ft_printf("value = %s0\n\n", current->value);
		current = current->next;
	}
}
