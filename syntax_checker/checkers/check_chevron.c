/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevron.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:30:58 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/01 17:31:23 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_chevron_util1(char *line, int *i, int *double_cote)
{
	if (line[*i] && line[*i] == '<' && line[(*i) - 1] == '>')
		return (msg_syntax_error(line[*i]), 0);
	if (line[*i] == '<' || line[*i] == '>')
	{
		(*i)++;
		*double_cote = 1;
	}
	while (line[*i] && space(line[*i]))
	{
		(*i)++;
		if (line[*i] && (line[*i] == '>' || line[*i] == '<'))
			return (msg_syntax_error(line[*i]), 0);
	}
	return (1);
}

int	check_chevron_util2(char *line, int *check, int *i, int *double_cote)
{
	int	upper;

	upper = 0;
	if (line[*i] == '>')
		upper = 1;
	*check = 0;
	(*i)++;
	*double_cote = 0;
	if (check_chevron_util1(line, i, double_cote) == 0)
		return (0);
	if (line[*i] && ((*double_cote) == 1) && (line[*i] == '>'
			|| line[*i] == '<'))
		return (msg_syntax_error(line[*i]), 0);
	if (line[*i] && ((upper == 1) || ((*double_cote == 1))) && line[*i] == '|')
		return (msg_syntax_error(line[*i]), 0);
	if (line[*i] && line[*i] == '|')
		*check = 1;
	while (line[*i] && line[*i] != '|' && line[*i] != '<' && line[*i] != '>'
		&& !space(line[*i]))
	{
		*check = 1;
		(*i)++;
	}
	return (1);
}

int	check_chevron(char *line)
{
	int	check;
	int	i;
	int	double_cote;

	check = 1;
	i = 0;
	double_cote = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			if (check_chevron_util2(line, &check, &i, &double_cote) == 0)
				return (0);
		}
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}
