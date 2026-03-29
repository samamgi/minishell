/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:48 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 22:12:26 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_n(char *str)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (str[i] == 'n')
            i++;
        else
            return (0);
    }
    return (1);
}

int ft_echo(t_cmd *pipes)
{
    int flag_n;
    int i;

    flag_n = 0;
    i = 1;
    while (pipes->args[i] && pipes->args[i][0] == '-' && pipes->args[i][1] == 'n' && check_n(pipes->args[i]))
    {
        flag_n = 1;
        i++;
    }
    while (pipes->args[i])
    {
        ft_printf("%s", pipes->args[i]);
        if (pipes->args[i + 1])
            ft_printf(" ");
        i++;
    }
    if (flag_n == 0)
        ft_printf("\n");
    return (0);
}
