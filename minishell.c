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

int g_signumber = 0;

t_env *set_env_list(char **env)
{
    t_env *head;
    t_env *current;
    t_env *new_node;
    char *equal;
    char *key;
    char *value;
    int i;

    head = NULL;
    current = NULL;
    i = 0;
    while (env[i])
    {
        equal = ft_strchr(env[i], '=');
        if (equal)
        {
            key = ft_substr(env[i], 0, equal - env[i]);
            value = ft_strdup(equal + 1);
        }
        else
        {
            key = ft_strdup(env[i]);
            value = ft_strdup("");
        }
        if (!key || !value)
        {
            free(key);
            free(value);
            free_env(head);
            return (NULL);
        }
        new_node = (t_env *)malloc(sizeof(t_env));
        if (!new_node)
        {
            free(key);
            free(value);
            free_env(head);
            return (NULL);
        }
        new_node->key = key;
        new_node->value = value;
        new_node->next = NULL;
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        i++;
    }
    return (head);
}

char *get_env_value(t_env *env_list, char *key)
{
    while (env_list)
    {
        if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}

char **env_list_to_array(t_env *env_list)
{
    char **env_tab;
    int count;
    int i;
    t_env *tmp;

    count = 0;
    tmp = env_list;
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    env_tab = (char **)malloc(sizeof(char *) * (count + 1));
    if (!env_tab)
        return (NULL);
    env_tab[count] = NULL;
    i = 0;
    while (env_list)
    {
        env_tab[i] = ft_strjoin(env_list->key, "=");
        if (env_list->value)
            env_tab[i] = strjoin_and_free(env_tab[i], env_list->value);
        env_list = env_list->next;
        i++;
    }
    return (env_tab);
}

void free_env(t_env *env_list)
{
    t_env *tmp;

    while (env_list)
    {
        tmp = env_list;
        env_list = env_list->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

void	increment_shlvl(t_env **env_list)
{
	char	*shlvl_str;
	int		shlvl_val;
	char	*new_shlvl;

	shlvl_str = get_env_value(*env_list, "SHLVL");
	if (shlvl_str)
		shlvl_val = ft_atoi(shlvl_str) + 1;
	else
		shlvl_val = 1;
	new_shlvl = ft_itoa(shlvl_val);
	if (!new_shlvl)
		return ;
	set_env_value(env_list, "SHLVL", new_shlvl);
	free(new_shlvl);
}

void	update_last_arg(t_env **env_list, char *cmd)
{
	if (cmd)
		set_env_value(env_list, "_", cmd);
}

int main(int ac, char **av, char **env)
{
    char *line;
    t_token *lst;
    t_cmd *pipes;
    t_env *env_list;
    char **env_tab;

    setup_signal();
    
    (void)ac;
    (void)av;
    (void)env;
    lst = NULL;
    pipes = NULL;
    env_list = NULL;
    env_tab = NULL;
    if (env)
    {
        env_list = set_env_list(env);
        if (env_list)
            increment_shlvl(&env_list);
        if (!env_list)
            ft_free(env_list);
    }
    while (1)
    {
        free_cmd(pipes);
        pipes = NULL;
        lst = NULL;
        env_tab = NULL;
        set_readline_state(1);
        line = readline("minishell: ");
        set_readline_state(0);
        if (!line)
        {
            ft_putendl_fd("exit", 1);
            break;
             //continue;
        }
        if (syntax_checker(line) == 1)
        {
            line = expand_variables(line, env_list);
            lst = set_tokens(line);
            free(line);
            pipes = parse_all(lst);
            prepare_heredocs(pipes);
            if (check_builtin(pipes) && !pipes->next)
            {
                if (pipes->args[0])
                    update_last_arg(&env_list, pipes->args[0]);
                execute_builtin(pipes, &env_list);
                free_cmd(pipes);
                pipes = NULL;
                continue;
            }
            else
            {
                env_tab = env_list_to_array(env_list);
                if (!pipex(pipes, env_tab))
                {
                    free_split(env_tab);
                    env_tab = NULL;
                    continue;
                }
                free_split(env_tab);
                env_tab = NULL;
            }
        }
    }
    free_env(env_list);
    return (0);
}