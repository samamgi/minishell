/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssadi-ou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2025/05/13 07:33:45 by ssadi-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*typedef enum e_redir_type
{
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_redir_type;*/

typedef struct s_redir
{
	t_token_type	type;
	char		*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		**args;
	t_redir		*redir;
	struct s_cmd	*next;
}	t_cmd;

t_redir	*set_redir(t_token_type token, char *value)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = token;
	new->file = value;
	new->next = NULL;
	return (new);
}

void	parse_tokens(t_token *lst)
{
	t_cmd	*pipes;
	t_token	*current;
	t_redir	*next;
	int	i;

	if (!lst)
		return;
	pipes = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pipes)
		return;
	i = 0;
	current = lst;
	while (current)
	{
		if (current->type == T_CMD)
		{
			while (current && (current->type == T_CMD || current->type == T_ARG))
			{
				i++;
				current = current->next;
			}
		}
		else
			current = current->next;
	}
	current = lst;
	pipes->args = (char **)malloc(sizeof(char *) * (i + 1));
	(pipes->args)[i] = NULL;
	i = 0;
	while (current)
        {
                if (current->type == T_CMD || current->type == T_ARG)
                {
			(pipes->args)[i] = current->value;
			i++;
                }
		current = current->next;
        }
	current = lst;
	i = 0;
	while (current)
	{
		if (current && (current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND || current->type == T_HEREDOC))
		{
			(pipes->redir) = set_redir(current->type, current->value);
			next = (pipes->redir);
			current = current->next;
			while (current && (current->type == T_REDIR_IN || current->type == T_REDIR_OUT || current->type == T_REDIR_APPEND || current->type == T_HEREDOC))
			{
				next->next = set_redir(current->type, current->value);
				next = next->next;
				current = current->next;
			}
		}
		else
			current = current->next;
	}
	pipes->next = NULL;
	i = 0;
	ft_printf("Pipe_struct 1 :\n\n");
	ft_printf("Cmd : %s\n", (pipes->args[i]));
	i++;
	while ((pipes->args)[i] != NULL)
	{
		ft_printf("Cmd ARGS : %s\n", (pipes->args[i]));
		i++;
	}
	ft_printf("\nRedirections :\n");
	next = (pipes->redir);
	while (next)
	{
		if (next->type == T_REDIR_IN)
			ft_printf("Redirection type : REDIR_IN ");
		if (next->type == T_REDIR_OUT)
                        ft_printf("Redirection type : REDIR_OUT ");
		if (next->type == T_REDIR_APPEND)
                        ft_printf("Redirection type : REDIR_APPEND ");
		if (next->type == T_HEREDOC)
                        ft_printf("Redirection type : HEREDOC ");
		ft_printf("Redirection file : %s\n", next->file);
		next = next->next;
	}	

}

int	main(int ac, char **av)
{
	char	*line;
	t_token	*lst;
	t_cmd	*pipes;

	(void)av;
	(void)ac;
	lst = NULL;
	pipes = NULL;
	/*while (1)
	{*/
		//line = readline("minishell: ");
		// line = "< infile echo arg1 arg2 arg3 | echo2 arg1 arg2 arg3 > outfile";
		// line = NULL;
		line = "echo test1 test2 test3 > arg1 >> arg2 < arg3";
		if (ft_strnstr(line, "exit", 4))
		{
			free(line);
			//break ;
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
			parse_tokens(lst);
			//token_clear(lst);
		}
	//}
	return (0);
}
