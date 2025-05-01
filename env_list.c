/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymen <aymen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 00:00:00 by aymen             #+#    #+#             */
/*   Updated: 2026/03/30 00:00:00 by aymen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_env_entry(t_env **head, t_env **tail, char *entry)
{
	t_env	*node;
	char	*equal;

	node = malloc(sizeof(t_env));
	if (!node)
		return (1);
	equal = ft_strchr(entry, '=');
	if (equal)
		node->key = ft_substr(entry, 0, equal - entry);
	else
		node->key = ft_strdup(entry);
	if (equal)
		node->value = ft_strdup(equal + 1);
	else
		node->value = ft_strdup("");
	if (!node->key || !node->value)
		return (free(node->key), free(node->value), free(node), 1);
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (0);
}

t_env	*set_env_list(char **env)
{
	t_env	*head;
	t_env	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (env && env[i])
	{
		if (append_env_entry(&head, &tail, env[i]))
		{
			free_env(head);
			return (NULL);
		}
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
	t_env	*tmp;
	int		count;
	int		i;

	count = 0;
	i = 0;
	tmp = env_list;
	while (tmp && ++count)
		tmp = tmp->next;
	env_tab = malloc(sizeof(char *) * (count + 1));
	if (!env_tab)
		return (NULL);
	env_tab[count] = NULL;
	tmp = env_list;
	while (i < count)
	{
		env_tab[i] = ft_strjoin(tmp->key, "=");
		if (tmp->value)
			env_tab[i] = strjoin_and_free(env_tab[i], tmp->value);
		tmp = tmp->next;
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
