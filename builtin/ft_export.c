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

void	print_export(t_env *env)
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

static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	return (new_node);
}

int	add_update_env(t_env **env_list, char *key, char *value)
{
	t_env	*current;
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
	current = create_env_node(key, value);
	if (!current)
		return (1);
	if (!*env_list)
		return (*env_list = current, 0);
	last = *env_list;
	while (last->next)
		last = last->next;
	last->next = current;
	return (0);
}

static int	handle_export_arg(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;
	char	*equal;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		key = ft_substr(arg, 0, equal - arg);
		value = equal + 1;
	}
	else
	{
		key = ft_strdup(arg);
		value = "";
	}
	if (!key)
		return (1);
	if (key[0] && add_update_env(env_list, key, value) != 0)
	{
		free(key);
		return (1);
	}
	free(key);
	return (0);
}

int	ft_export(t_cmd *pipes, t_env **env_list)
{
	int	i;

	i = 1;
	if (!pipes->args[1])
	{
		print_export(*env_list);
		return (0);
	}
	while (pipes->args[i])
	{
		if (handle_export_arg(pipes->args[i], env_list))
			return (1);
		i++;
	}
	return (0);
}
