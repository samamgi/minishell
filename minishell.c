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

t_global	g_shell = {0, NULL, 0, 0};

static t_env	*init_env_list(char **env)
{
	t_env	*env_list;

	env_list = NULL;
	if (env)
		env_list = set_env_list(env);
	if (env_list)
		increment_shlvl(&env_list);
	g_shell.env_global = env_list;
	return (env_list);
}

static void	execute_parsed(t_cmd *pipes, t_env **env_list)
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
		g_shell.signumber = status;
		g_shell.env_global = *env_list;
		return ;
	}
	env_tab = env_list_to_array(*env_list);
	if (!env_tab)
		return ;
	pipex(pipes, env_tab);
	free_split(env_tab);
}

static void	handle_line(char *line, t_env **env_list)
{
	char	*expanded;
	t_token	*lst;
	t_cmd	*pipes;

	if (syntax_checker(line) != 1)
		return ;
	expanded = expand_variables(line, *env_list);
	lst = set_tokens(expanded);
	free(expanded);
	pipes = parse_all(lst);
	if (!prepare_heredocs(pipes))
	{
		free_cmd(pipes);
		return ;
	}
	execute_parsed(pipes, env_list);
	free_cmd(pipes);
}

static void	cleanup_shell(t_env *env_list)
{
	ft_putendl_fd("exit", 1);
	clear_history();
	rl_clear_history();
	free_env(env_list);
	g_shell.env_global = NULL;
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*env_list;

	(void)ac;
	(void)av;
	setup_signal();
	using_history();
	env_list = init_env_list(env);
	while (1)
	{
		set_readline_state(1);
		line = readline("minishell: ");
		set_readline_state(0);
		if (!line)
			break ;
		if (line[0])
			add_history(line);
		handle_line(line, &env_list);
		free(line);
	}
	cleanup_shell(env_list);
	return (0);
}
