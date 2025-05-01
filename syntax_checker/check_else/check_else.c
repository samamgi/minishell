/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_else.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:03:04 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/01 17:03:53 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	space(char c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

void	msg_syntax_error(char c)
{
	if (c == 0)
		ft_printf("bash: syntax error near unexpected token `newline'\n");
	else
		ft_printf("bash: syntax error near unexpected token `%c'\n", c);
}

int	check_else(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '`' || line[i] == ';' || line[i] == '(' || line[i] == ')'
			|| line[i] == '&' || line[i] == '{' || line[i] == '}')
		{
			if (line[i] == ';' && line[i + 1] && line[i + 1] == ';')
				ft_printf("bash: syntax error near unexpected token `;;'\n");
			else if (line[i] == '&' && line[i + 1] && line[i + 1] == '&')
				ft_printf("bash: syntax error near unexpected token `&&'\n");
			else
				msg_syntax_error(line[i]);
			return (0);
		}
		i++;
	}
	return (1);
}
