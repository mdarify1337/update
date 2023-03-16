/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:03:31 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/12 13:19:39 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	delete_node_by_key(t_env *head, char *key)
{
	t_env_node	*tmp;

	if (!head->first ||!key)
		return (0);
	tmp = head->first;
	if (ft_strcmp(tmp->key, key) == 0)
	{
		head->first = tmp->next;
		head->first->previous = NULL;
		free(tmp);
		return (0);
	}
	while (tmp && ft_strcmp(tmp->key, key) != 0)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		tmp->previous->next = tmp->next;
		tmp->next->previous = tmp->previous;
		free(tmp);
		return (1);
	}
	return (0);
}

int	unset_cmd(t_env *env, char *key)
{
	return (delete_node_by_key(env, key));
}

void	exec_unset(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->cmd_[i] == NULL)
		return ;
	while (cmd->cmd_[i])
	{
		unset_cmd(*env, cmd->cmd_[i]);
		i++;
	}
}
