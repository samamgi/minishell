/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:51 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 21:53:02 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_env_value(t_env **env_list, char *key, char *value)
{
    t_env *current;

    if (!env_list || !key)
        return;

    current = *env_list;
    while (current)
    {
        if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
        {
            free(current->value);
            if (value)
                current->value = ft_strdup(value);
            else
                current->value = ft_strdup("");  
            return;
        }
        current = current->next;
    }

    t_env *new_node = malloc(sizeof(t_env));
    if (!new_node)
        return;
    new_node->key = ft_strdup(key);
    if (value)
        new_node->value = ft_strdup(value);
    else
        new_node->value = ft_strdup(""); 
    new_node->next = *env_list;
    *env_list = new_node;
}

int ft_env(t_env *env)
{
    t_env *current;

    current = env;
    while (current)
    {
        if (current->value)
            printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return (0);
}