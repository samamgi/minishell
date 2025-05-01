/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:31:14 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/04/25 19:46:14 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

int	space(char c)
{
	return ( c == 32 || (c>= 9 && c <= 13));
}

void	msg_syntax_error(char c)
{
	if (c == 0)
		ft_printf("bash: syntax error near unexpected token `newline'\n");
	else
		ft_printf("bash: syntax error near unexpected token `%c'\n", c);
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
		{
			if (line[i] && line[i] == 39)
			{
				check = 0;
				i++;
				while (line[i])
				{
					if (line[i] == 39)
					{
						check = 1;
						i++;
						break;
					}
					line[i] *= -1;
					i++;
				}
			}
			if (line[i] && line[i] == 34)
                	{
                        	check = 0;
                        	i++;
                        	while (line[i])
                        	{
                                	if (line[i] == 34)
                                	{
                                        	check = 1;
                                        	i++;
                                        	break;
                                	}
                                	line[i] *= -1;
                                	i++;
                        	}
                	}
		}
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}

int	check_chevron(char *line)
{
	int	check;
	int	i;
	int	upper;
	int	double_cote;

	check = 1;
	i = 0;
	double_cote = 0;
	while (line[i]) 
	{
		if (line[i] == '<' || line[i] == '>')
		{
			upper = 0;
			if (line[i] == '>')
				upper = 1;
			check = 0;
			i++;
			double_cote = 0;
			if (line[i] && line[i] == '<' && line[i - 1] == '>')
                                return (msg_syntax_error(line[i]), 0);
			if (line[i] == '<' || line[i] == '>')
			{
				i++;
				double_cote = 1;
			}
			while (line[i] && space(line[i]))
			{
				i++;
				if (line[i] && (line[i] == '>' || line[i] == '<'))
                                        return (msg_syntax_error(line[i]), 0);
			}
			if (line[i] && double_cote == 1 && (line[i] == '>' || line[i] == '<'))
				return (msg_syntax_error(line[i]), 0);
			if (line[i] && ((upper == 0) || (double_cote == 1)) && line[i] == '|')
				return (msg_syntax_error(line[i]), 0);
			if (line[i] && line[i] == '|')
				check = 1;
			while (line[i] && 
				line[i] != '|' && 
				line[i] != '<' && 
				line[i] != '>' && 
				!space(line[i]))
			{
				check = 1;
				i++;
			}
		}
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}

int	check_pipe(char *line)
{
	int	i;
	int	check;
	int	char_nospace;
	int	upper;

	i = 0;
	check = 1;
	char_nospace = 0;
	while (line[i])
	{
		upper = 0;
		if (line[i] && line[i] != '<' && line[i] != '|' && !space(line[i]))
		{
			upper = 0;
			if (line[i] == '>')
				upper = 1;
			i++;
			if (!line[i])
			{
				if (check == 0)
					msg_syntax_error(line[i]);
				return (check);
			}
			char_nospace = 1;
		}
		if (line[i] && line[i] == '|')
		{
			if (char_nospace == 0)
				return (msg_syntax_error(line[i]), 0);
			i++;
			check = 0;
			while (line[i] && space(line[i]))
				i++;
			if (!line[i])
				return (msg_syntax_error(line[i]), check);
			if (line[i] == '|')
				return (msg_syntax_error(line[i]), 0);
			if (line[i] && upper == 1 && (line[i] == '>' || line[i] == '<'))
				return (msg_syntax_error(line[i]), 0);
			if (line[i] && line[i] != '|' && !space(line[i]))
			{
					check = 1;
					i++;
			}
			upper = 0;
			char_nospace = 0;
		}
		else
			i++;
	}
	if (check == 0)
		msg_syntax_error(line[i]);
	return (check);
}

int	check_else(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '`' || line[i] == ';' || line[i] == '(' || line[i] == ')' || line[i] == '&' || line[i] == '{' || line[i] == '}')
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

int     syntax_checker(char *line)
{
	if (ft_strlen(line) == 0)
		return (1);
	if (!line)
		return (0);
	if (check_cote(line) == 0 || check_pipe(line) == 0 || check_chevron(line) == 0 || check_else(line) == 0)
                return (0);
        return (1);
}

int	main(int ac, char **av)
{
		char	*line;
	
		(void)av;
		(void)ac;
		while (1)
		{
			line = readline("minishell: ");
			if (ft_strnstr(line, "exit", 4))
			{
				free(line);
				break;
			}
			syntax_checker(line);
			free(line);
		}
	return (0);
}
