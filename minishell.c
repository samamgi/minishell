/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:02:50 by ssadi-ou          #+#    #+#             */
/*   Updated: 2026/03/05 22:41:48 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_parsed(t_cmd *pipes, t_env **env_list, int *last_status)
{
	char	**env_tab;
	int		status;

	if (check_builtin(pipes) && !pipes->next)
	{
		if (pipes->args[0])
			update_last_arg(env_list, pipes->args[0]);
		if (pipes->redir)
			status = apply_redir_builtin(pipes, env_list);
		else
			status = execute_builtin(pipes, env_list);
		if (status < 0)
			status = 1;
		*last_status = status;
		return ;
	}
	env_tab = env_list_to_array(*env_list);
	if (!env_tab)
		return ;
	pipex(pipes, env_tab, last_status);
	free_split(env_tab);
}

static void	handle_line(char *line, t_env **env_list, int *last_status)
{
	char	*expanded;
	t_token	*lst;
	t_cmd	*pipes;

	if (syntax_checker(line) != 1)
		return ;
	expanded = expand_variables(line, *env_list, *last_status);
	if (!expanded)
		return ;
	lst = set_tokens(expanded);
	free(expanded);
	pipes = parse_all(lst);
	if (!prepare_heredocs(pipes, *env_list, last_status))
	{
		free_cmd(pipes);
		return ;
	}
	execute_parsed(pipes, env_list, last_status);
	free_cmd(pipes);
}

static void	cleanup_shell(t_env *env_list)
{
	ft_putendl_fd("exit", 1);
	clear_history();
	rl_clear_history();
	free_env(env_list);
}

static int	read_prompt(char **line, int *last_status)
{
	*line = readline("minishell: ");
	if (g_signal == SIGINT)
	{
		*last_status = 130;
		g_signal = 0;
	}
	if (!*line)
		return (0);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*env_list;
	int		last_status;

	(void)ac;
	(void)av;
	last_status = 0;
	setup_signal();
	using_history();
	env_list = NULL;
	if (env)
		env_list = set_env_list(env);
	if (env_list)
		increment_shlvl(&env_list);
	while (read_prompt(&line, &last_status))
	{
		if (line[0])
			add_history(line);
		handle_line(line, &env_list, &last_status);
		free(line);
	}
	cleanup_shell(env_list);
	return (0);
}
