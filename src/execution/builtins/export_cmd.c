/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:47:05 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 16:56:24 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	find_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_swap(t_env_node *n1, t_env_node *n2)
{
	char	*key;
	char	*val;

	key = n1->key;
	val = n1->value;
	n1->key = n2->key;
	n1->value = n2->value;
	n2->key = key;
	n2->value = val;
}

void	ft_sort(t_env *env)
{
	t_env_node	*current;

	current = env->first;
	while (current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			ft_swap(current, current->next);
			current = env->first;
		}
		else
			current = current->next;
	}
}

void	print_env_sorted(t_env *env)
{
	t_env_node	*current;

	if (!env->first)
		return ;
	ft_sort(env);
	current = env->first;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

void	export_cmd(t_env	*env, char *arg)
{
	t_env_node	*node;
	int			i;
	t_env_node	*node_;

	node = env->first;
	i = ft_strchr(arg, '=');
	if (!arg)
		print_env_sorted(env);
	else if (!arg || !ft_is_alpha(arg[0]))
		printf("minishell : export : `%s` not a valid identifier", arg);
	else if (arg[i - 1] && arg[i - 1] == '+')
		export_with_join(&env, arg, i, NULL);
	else if (!node)
		insert_to_tail(&env, env_new(arg));
	else if (i != -1 && search_by_key(node, ft_substr(arg, 0, i)) != NULL)
	{
		node_ = search_by_key(node, ft_substr(arg, 0, i));
		if (node_)
		{
			free(node_->value);
			node_->value = ft_substr(arg, i + 1, ft_strlen(arg) - i);
		}
	}
	else if (search_by_key(node, arg) == NULL)
		insert_to_tail(&env, env_new(arg));
}

void	exec_export(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->cmd_[i] == NULL)
	{
		export_cmd(*env, NULL);
		return ;
	}
	while (cmd->cmd_[i])
	{
		export_cmd(*env, cmd->cmd_[i]);
		i++;
	}
}
