/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/01 19:03:17 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			break ;
		}
		syntax_checker(line);
		free(line);
	}
	return (0);
}
