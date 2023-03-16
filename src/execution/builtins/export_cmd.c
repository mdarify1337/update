/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:47:05 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 13:42:51 by mdarify          ###   ########.fr       */
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
	t_env		*tmp;
	t_env_node	*current;

	tmp = env;
	ft_sort(tmp);
	current = tmp->first;
	while (current)
	{
		printf("declare -x %s", current->key);
		if (current->value != NULL)
			printf("=\"%s\"", current->value);
		printf("\n");
		current = current->next;
	}
}

char	*ft_strcat(char *pdf, char *s1, char *s2)
{
	int	l1;
	int	l2;
	int	l3;

	l1 = 0;
	l2 = 0;
	l3 = 0;
	while (s1[l2])
	{
		pdf[l1] = s1[l2];
		l1++;
		l2++;
	}
	while (s2[l3])
	{
		pdf[l1 + l3] = s2[l3];
		l3++;
	}
	pdf[l1 + l3] = '\0';
	return (pdf);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*pdf;
	int		l1;
	int		l2;

	if (!s2)
		return (0);
	if (!s1)
	{
		s1 = malloc(1);
		*s1 = '\0';
	}
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2) + 1;
	pdf = malloc(l1 + l2);
	if (!pdf)
	{
		free(s1);
		return (NULL);
	}
	pdf = ft_strcat(pdf, s1, s2);
	free(s1);
	return (pdf);
}

void	add_env2(t_env **env_list, t_env_node *node)
{
	if (!node)
		return ;
	if ((*env_list) && (*env_list)->first == NULL)
		(*env_list)->first = node;
	else
	{
		(*env_list)->last->next = node;
		node->previous = (*env_list)->last;
	}
	(*env_list)->last = node;
}

void	export_join_plus(t_env *env, char *arg)
{
	t_env_node	*node;
	t_env_node	*new_node;
	int			l;

	if (!env->first)
		return ;
	node = env->first;
	l = ft_strchr(arg, '+');
	if (!ft_is_alpha(arg[0]))
	{
		printf("minishell ---> 1: export : `%s` not a valid identifie\n", arg);
		g_fcode.exit_status = 1;
	}
	else if (l != -1 && search_by_key(node, ft_substr(arg, 0, l)) != NULL)
	{
		if (arg[l + 1] == '=')
		{
			new_node = search_by_key(node, ft_substr(arg, 0, l));
			if (new_node)
			{
				new_node->value = ft_strjoin2(ft_strjoin2(ft_substr(arg, 0, l), "="), new_node->value);
				new_node->value = ft_strjoin2(new_node->value, ft_substr(arg, l+ 2, ft_strlen(arg) - l));
			}
		}
	}
	else
	{
		printf("heerr\n");
		insert_to_tail(&env->last, env_new(arg));
	}
}

void	export_cmd(t_env *env, char *arg)
{
	t_env_node	*node;
	int			i;
	t_env_node	*node_;

	if (!env->first)
		return ;
	node = env->first;
	i = ft_strchr(arg, '=');
	if (ft_strchr(arg, '+') != -1)
		export_join_plus(env, arg);
	else if (!arg || !ft_is_alpha(arg[0]))
		printf("minishell : export : `%s` not a valid identifier\n",
				arg);
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
		insert_to_tail(&env->last, env_new(arg));
}

void	exec_export(t_cmd_node *cmd, t_env **env)
{
	int	i;

	i = 1;
	if (cmd->cmd_[i] == NULL)
	{
		print_env_sorted(*env);
		return ;
	}
	while (cmd->cmd_[i])
	{
		export_cmd(*env, cmd->cmd_[i]);
		i++;
	}
}
