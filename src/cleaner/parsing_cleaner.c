/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:25:44 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 11:53:28 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_lexer_cleaner(t_list *lst)
{
	t_element	*elm;
	t_element	*ptr;

	elm = lst->first;
	ptr = elm;
	while (elm)
	{
		ptr = ptr->next;
		free(elm->content);
		free(elm);
		elm = ptr;
	}
	free(lst);
}

void	ft_env_cleaner(t_env_node *lst)
{
	t_env_node	*tmp;
	t_env_node	*tmp2;

	tmp = lst;
	tmp2 = tmp;
	while (tmp)
	{
		tmp2 = tmp2->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = tmp2;
	}
}

void	free_2d_array(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		free(arg[i++]);
	free(arg);
}

void	ft_cmd_cleaner(t_cmd_node **cmd)
{
	t_cmd_node	*tmp;
	int			i;

	while (*cmd)
	{
		i = 0;
		tmp = (*cmd)->next;
		while ((*cmd) && (*cmd)->cmd_[i])
		{
			free((*cmd)->cmd_[i]);
			i++;
		}
		free((*cmd)->cmd_);
		free((*cmd)->args);
		free(*cmd);
		*cmd = tmp;
	}
}

void	ft_parsing_cleaner(t_list *lst, t_cmd_node *node, t_env *env)
{
	(void)env;
	ft_cmd_cleaner(&node);
	ft_lexer_cleaner(lst);
}
