/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/17 04:18:10 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// line = "< infile echo arg1 arg2 arg3 | echo2 arg1 arg2 arg3 > outfile";
	// line = NULL;
	//line = "echo arg1 > file1 arg2 > file2 arg3 > file3 >> file4 < file5 arg4 | echo > file1 arg1 arg2 <<file2 | cat arg1 ar2 | echo >file1 arg";
	if (ft_strnstr(line, "exit", 4))
	{
		free(line);
		// break ;
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
	}
	return (0);
}
