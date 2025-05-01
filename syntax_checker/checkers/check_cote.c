/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:00:40 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/01 17:02:28 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_cote_util1(char *line, int *i, int *check)
{
	*check = 0;
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == 39)
		{
			*check = 1;
			(*i)++;
			break ;
		}
		line[*i] *= -1;
		(*i)++;
	}
}

void	check_cote_util2(char *line, int *i, int *check)
{
	*check = 0;
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == 34)
		{
			*check = 1;
			(*i)++;
			break ;
		}
		line[*i] *= -1;
		(*i)++;
	}
}

void	check_cote_util3(char *line, int *i, int *check)
{
	if (line[*i] && line[*i] == 39)
		check_cote_util1(line, i, check);
	if (line[*i] && line[*i] == 34)
		check_cote_util2(line, i, check);
}

int	check_cote(char *line)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (line[i])
	{
		if (line[i] && (line[i] == 39 || line[i] == 34))
			check_cote_util3(line, &i, &check);
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}
