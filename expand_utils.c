/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by aymen             #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_doublecotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				line[i] *= -1;
				i++;
			}
		}
		i++;
	}
}

void	expand_util(char *line, int *i, char **result, t_env *env_list)
{
	int		start;
	char	*varname;
	char	*value;

	(*i)++;
	start = (*i);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	varname = ft_substr(line, start, (*i) - start);
	if (env_list)
		value = get_env_value(env_list, varname);
	else
		value = getenv(varname);
	if (value)
		*result = strjoin_and_free(*result, value);
	free(varname);
}
