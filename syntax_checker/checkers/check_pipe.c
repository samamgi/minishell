/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:52:07 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/01 18:52:18 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_util1(char *line, int *i, int *check)
{
	if (!line[*i])
	{
		if (*check == 0)
			msg_syntax_error(line[*i]);
		return (*check);
	}
	return (1);
}

void	check_pipe_util2(char *line, int *i, int *check, int *char_nospace)
{
	if (line[*i] && line[*i] != '|' && !space(line[*i]))
	{
		*check = 1;
		(*i)++;
	}
	*char_nospace = 0;
}

int	check_pipe_util3(char *line, int *i, int *check, int *char_nospace)
{
	if (*char_nospace == 0)
		return (msg_syntax_error(line[*i]), 0);
	(*i)++;
	*check = 0;
	while (line[*i] && space(line[*i]))
		(*i)++;
	if (!line[*i])
		return (msg_syntax_error(line[*i]), *check);
	if (line[*i] == '|')
		return (msg_syntax_error(line[*i]), 0);
	return (1);
}

int	check_pipe_util4(char *line, int *i, int *check, int *char_nospace)
{
	int	upper;

	upper = 0;
	if (line[*i] && line[*i] != '<' && line[*i] != '|' && !space(line[*i]))
	{
		upper = 0;
		if (line[*i] == '>')
			upper = 1;
		(*i)++;
		if (check_pipe_util1(line, i, check) == 0)
			return (0);
		*char_nospace = 1;
	}
	if (line[*i] && line[*i] == '|')
	{
		if (check_pipe_util3(line, i, check, char_nospace) == 0)
			return (0);
		if (line[*i] && (upper) == 0 && (line[*i] == '>' || line[*i] == '<'))
			return (msg_syntax_error(line[*i]), 0);
		check_pipe_util2(line, i, check, char_nospace);
		upper = 0;
	}
	return (1);
}

int	check_pipe(char *line)
{
	int	i;
	int	check;
	int	char_nospace;

	i = 0;
	check = 1;
	char_nospace = 0;
	while (line[i])
	{
		if ((line[i] && line[i] != '<' && line[i] != '|' && !space(line[i]))
			|| (line[i] && line[i] == '|'))
		{
			if (check_pipe_util4(line, &i, &check, &char_nospace) == 0)
				return (0);
		}
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}
