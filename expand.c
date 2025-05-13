/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 03:02:51 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 02:25:10 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_and_free(char *s1, char const *s2)
{
	char	*str;
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[j])
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (free(s1), str);
}

void	set_doublecotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] != '\0' && line[i] != '"')
			{
				line[i] *= -1;
				i++;
			}
		}
		i++;
	}
}

void	expand_util(char *line, int *i, char **result)
{
	int		start;
	char	*varname;
	char	*value;

	(*i)++;
	start = (*i);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	varname = ft_substr(line, start, (*i) - start);
	value = getenv(varname);
	if (value)
		*result = strjoin_and_free(*result, value);
	free(varname);
}

char	*expand_variables(char *line)
{
	int		i;
	char	tmp[2];
	char	*result;

	if (ft_strlen(line) == 0)
		return (NULL);
	set_doublecotes(line);
	result = malloc(1);
	result[0] = '\0';
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && (ft_isalnum(line[i + 1]) || line[i
					+ 1] == '_'))
			expand_util(line, &i, &result);
		else
		{
			tmp[0] = line[i];
			tmp[1] = '\0';
			result = strjoin_and_free(result, tmp);
			i++;
		}
	}
	set_doublecotes(result);
	return (result);
}

/*int	main(int ac, char **av)
{
	char	*line;

	(void)av;
	(void)ac;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
			return (0);
		if (ft_strnstr(line, "exit", 4))
		{
			free(line);
			return (0);
		}
		if (syntax_checker(line) == 1)
			line = expand_variables(line);
		free(line);
	}
	return (0);
}*/
