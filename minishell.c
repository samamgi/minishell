/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/18 20:32:21 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *line;
	t_token *lst;
	t_cmd *pipes;

	(void)ac;
	(void)av;
	(void)env;
	lst = NULL;
	pipes = NULL;
	while (1)
	{
		free_cmd(pipes);
		pipes = NULL;
		lst = NULL;
		line = readline("minishell: ");
		if (!line)
			continue;
		if (ft_strnstr(line, "exit", 4))
		{
			free(line);
			return (0);
		}
		if (syntax_checker(line) == 1)
		{
			line = expand_variables(line);
			lst = set_tokens(line);
			free(line);
			if (!lst)
				ft_printf("lst error\n");
			print_token(lst);
			printf("test \n\n\n\n");
			pipes = parse_all(lst);
			prepare_heredocs(pipes);
			printf("pipes addr %p\n", pipes);
			if (!pipex(pipes, env))
			{
				printf("pipes addr apres %p\n", pipes);
				printf("continue");
				continue;
			}
			printf("pipes addr apres %p\n", pipes);
		}
	}
	return (0);
}

