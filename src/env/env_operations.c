/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:38:23 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 16:55:46 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**convert_array(t_env *env)
{
	t_env_node	*tmp;
	char		**arr;
	int			i;
	int			size;

	i = 0;
	tmp = env->first;
	size = ft_lstsize(tmp);
	arr = calloc(size + 1, sizeof(char *));
	if (arr)
	{
		while (i < size)
		{
			arr[i] = ft_strdup(tmp->key);
			if (tmp->value)
			{
				arr[i] = ft_strjoin(arr[i], "=");
				arr[i] = ft_strjoin(arr[i], tmp->value);
			}
			tmp = tmp->next;
			i++;
		}
		arr[i] = NULL;
	}
	return (arr);
}

t_env_node	*search_by_key(t_env_node *head, char *key)
{
	t_env_node	*tmp;

	tmp = head;
	if (!head)
		return (NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	insert_to_tail(t_env **env, t_env_node *new)
{
	t_env_node	*tmp;

	tmp = (*env)->first;
	if (!(*env)->first)
	{
		(*env)->first = new;
		(*env)->first->previous = NULL;
	}	
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->previous = tmp;
	}
}
