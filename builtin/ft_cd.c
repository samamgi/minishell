/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 17:41:45 by aymen             #+#    #+#             */
/*   Updated: 2026/03/05 22:08:41 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int cd_home(t_env **env_list, char *oldpwd)
{
    char *home = get_env_value(*env_list, "HOME");
    if (!home)
    {
        ft_putstr_fd("minishell: cd: HOME not set\n", 2);
        free(oldpwd);
        return (1);
    }
    if (chdir(home) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(home, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        free(oldpwd);
        return (1);
    }
    set_env_value(env_list, "OLDPWD", oldpwd);
    free(oldpwd);

    char *newpwd = getcwd(NULL, 0);
    set_env_value(env_list, "PWD", newpwd);
    free(newpwd);
    return (0);
}

int cd_oldpwd(t_env **env_list, char *oldpwd)
{
    char *old = get_env_value(*env_list, "OLDPWD");
    if (!old)
    {
        ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
        free(oldpwd);
        return (1);
    }
    if (chdir(old) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(old, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        free(oldpwd);
        return (1);
    }
    ft_putendl_fd(old, 1);
    set_env_value(env_list, "OLDPWD", oldpwd);
    free(oldpwd);

    char *newpwd = getcwd(NULL, 0);
    set_env_value(env_list, "PWD", newpwd);
    free(newpwd);
    return (0);
}

int cd_path(t_env **env_list, char *path, char *oldpwd)
{
    if (chdir(path) != 0)
    {
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(strerror(errno), 2);
        free(oldpwd);
        return (1);
    }
    set_env_value(env_list, "OLDPWD", oldpwd);
    free(oldpwd);

    char *newpwd = getcwd(NULL, 0);
    set_env_value(env_list, "PWD", newpwd);
    free(newpwd);
    return (0);
}

int ft_cd(t_cmd *pipes, t_env **env_list)
{
    char *oldpwd;
    int ac;

    ac = 0;
    while (pipes->args[ac])
        ac++;

    if (ac > 2)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return (1);
    }

    oldpwd = getcwd(NULL, 0);
    if (!oldpwd)
        return (perror("getcwd"), 1);

    if (!pipes->args[1])
        return (cd_home(env_list, oldpwd));
    else if (ft_strncmp(pipes->args[1], "-", 2) == 0)
        return (cd_oldpwd(env_list, oldpwd));
    else
        return (cd_path(env_list, pipes->args[1], oldpwd));
}