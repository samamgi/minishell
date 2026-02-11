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

t_env	*set_env_list(char **env)
{
    t_env	*head;
    t_env	*current;
    char	**split;
    int		i;

    head = NULL;
    current = NULL;
    i = 0;
    while (env[i])
    {
        split = ft_split(env[i], '=');
        if (!split)
            return (NULL);
        if (!head)
        {
            head = (t_env *)malloc(sizeof(t_env));
            current = head;
        }
        else
        {
            current->next = (t_env *)malloc(sizeof(t_env));
            current = current->next;
        }
        current->key = ft_strdup(split[0]);
        if (split[1])
            current->value = ft_strdup(split[1]);
        else
            current->value = ft_strdup("");
        current->next = NULL;
        free_split(split);
        i++;
    }
    return (head);
}

char	*get_env_value(t_env *env_list, char *key)
{
    while (env_list)
    {
        if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
            return (env_list->value);
        env_list = env_list->next;
    }
    return (NULL);
}

char	**env_list_to_array(t_env *env_list)
{
    char	**env_tab;
    int		count;
    int		i;
    t_env	*tmp;

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

void	free_env(t_env *env_list)
{
    t_env	*tmp;

    while (env_list)
    {
        tmp = env_list;
        env_list = env_list->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
}

int	is_builtin(t_cmd *pipes)
{
    if (!pipes || !pipes->args || !pipes->args[0])
        return (0);
    if (ft_strncmp(pipes->args[0], "cd", 3) == 0
        || ft_strncmp(pipes->args[0], "echo", 5) == 0
        || ft_strncmp(pipes->args[0], "env", 4) == 0
        || ft_strncmp(pipes->args[0], "exit", 5) == 0
        || ft_strncmp(pipes->args[0], "export", 7) == 0
        || ft_strncmp(pipes->args[0], "pwd", 4) == 0
        || ft_strncmp(pipes->args[0], "unset", 6) == 0)
        return (1);
    return (0);
}

int	builtin_cd(t_cmd *pipes, t_env *env_list)
{
    char	*path;

    if (!pipes->args[1])
        path = get_env_value(env_list, "HOME");
    else
        path = pipes->args[1];
    if (!path)
    {
        ft_printf("cd: HOME not set\n");
        return (1);
    }
    if (chdir(path) == -1)
    {
        perror("cd");
        return (1);
    }
    return (0);
}

int	builtin_echo(t_cmd *pipes)
{
    int	i;

    i = 1;
    while (pipes->args[i])
    {
        ft_printf("%s", pipes->args[i]);
        if (pipes->args[i + 1])
            ft_printf(" ");
        i++;
    }
    ft_printf("\n");
    return (0);
}

int	builtin_env(t_env *env_list)
{
    t_env	*current;

    current = env_list;
    while (current)
    {
        ft_printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (0);
}

int	builtin_exit(t_cmd *pipes, t_env **env_list)
{
    int	exit_code;

    if (pipes->args[1])
        exit_code = ft_atoi(pipes->args[1]);
    else
        exit_code = 0;
    free_env(*env_list);
    free_cmd(pipes);
    exit(exit_code);
}

int	add_or_update_env(t_env **env_list, char *key, char *value)
{
    t_env	*current;
    t_env	*new_node;
    t_env	*last;

    current = *env_list;
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return (0);
        }
        current = current->next;
    }
    new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return (1);
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    new_node->next = NULL;
    if (!*env_list)
        *env_list = new_node;
    else
    {
        last = *env_list;
        while (last->next)
            last = last->next;
        last->next = new_node;
    }
    return (0);
}

int	builtin_export(t_cmd *pipes, t_env **env_list)
{
    int		i;
    char	**split;
    char	*value;

    i = 1;
    while (pipes->args[i])
    {
        split = ft_split(pipes->args[i], '=');
        if (!split)
            return (1);
        if (split[0])
        {
            if (split[1])
                value = split[1];
            else
                value = "";
            add_or_update_env(env_list, split[0], value);
        }
        free_split(split);
        i++;
    }
    return (0);
}

int	builtin_pwd(void)
{
    char	cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("pwd");
        return (1);
    }
    ft_printf("%s\n", cwd);
    return (0);
}

int	builtin_unset(t_cmd *pipes, t_env **env_list)
{
    int		i;
    t_env	*current;
    t_env	*prev;

    i = 1;
    while (pipes->args[i])
    {
        current = *env_list;
        prev = NULL;
        while (current)
        {
            if (ft_strncmp(current->key, pipes->args[i],
                    ft_strlen(pipes->args[i]) + 1) == 0)
            {
                if (prev)
                    prev->next = current->next;
                else
                    *env_list = current->next;
                free(current->key);
                free(current->value);
                free(current);
                break ;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return (0);
}

int	execute_builtin(t_cmd *pipes, t_env **env_list)
{
    if (ft_strncmp(pipes->args[0], "cd", 3) == 0)
        return (builtin_cd(pipes, *env_list));
    else if (ft_strncmp(pipes->args[0], "echo", 5) == 0)
        return (builtin_echo(pipes));
    else if (ft_strncmp(pipes->args[0], "env", 4) == 0)
        return (builtin_env(*env_list));
    else if (ft_strncmp(pipes->args[0], "exit", 5) == 0)
        return (builtin_exit(pipes, env_list));
    else if (ft_strncmp(pipes->args[0], "export", 7) == 0)
        return (builtin_export(pipes, env_list));
    else if (ft_strncmp(pipes->args[0], "pwd", 4) == 0)
        return (builtin_pwd());
    else if (ft_strncmp(pipes->args[0], "unset", 6) == 0)
        return (builtin_unset(pipes, env_list));
    return (-1);
}

int	main(int ac, char **av, char **env)
{
    char	*line;
    t_token	*lst;
    t_cmd	*pipes;
    t_env	*env_list;
    char	**env_tab;

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
        if (!env_list)
            ft_free(env_list);
    }
    while (1)
    {
        free_cmd(pipes);
        pipes = NULL;
        lst = NULL;
        env_tab = NULL;
        line = readline("minishell: ");
        if (!line)
            continue;
        if (syntax_checker(line) == 1)
        {
            line = expand_variables(line, env_list);
            lst = set_tokens(line);
            free(line);
            pipes = parse_all(lst);
            prepare_heredocs(pipes);
            if (is_builtin(pipes) && !pipes->next)
            {
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