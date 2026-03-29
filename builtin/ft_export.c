/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:56 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 21:02:33 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_export(t_env *env)
{
    while (env)
    {
        if (env->value)
            printf("export %s=\"%s\"\n", env->key, env->value);
        else
            printf("export %s\n", env->key);
        env = env->next;
    }
}

int add_update_env(t_env **env_list, char *key, char *value)
{
    t_env *current;
    t_env *new_node;
    t_env *last;

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

int ft_export(t_cmd *pipes, t_env **env_list)
{
    int i;
    char *equal;
    char *key;
    char *value;

    i = 1;
    if (!pipes->args[1])
    {
        print_export(*env_list);
        return (0);
    }
    while (pipes->args[i])
    {
        equal = ft_strchr(pipes->args[i], '=');
        if (equal)
        {
            key = ft_substr(pipes->args[i], 0, equal - pipes->args[i]);
            value = equal + 1;
        }
        else
        {
            key = ft_strdup(pipes->args[i]);
            value = "";
        }
        if (!key)
            return (1);
        if (key[0])
        {
            if (add_update_env(env_list, key, value) != 0)
            {
                free(key);
                return (1);
            }
        }
        free(key);
        i++;
    }
    return (0);
}