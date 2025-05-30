/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 06:34:02 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 06:35:08 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int ac, char **av)
{
	char	*line;
	t_token	*lst;
	t_cmd	*pipes;

	(void)av;
	(void)ac;
	lst = NULL;
	pipes = NULL;
	while (1)
	{
		line = readline("minishell: ");
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
			pipes = parse_all(lst);
			free_cmd(pipes);
		}
		return (0);
	}
