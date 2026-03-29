/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:42:01 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 21:02:30 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_unset(t_cmd *pipes, t_env **env_list)
{
    int i;
    t_env *current;
    t_env *prev;

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
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
    return (0);
}