/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:40:25 by mmounaji          #+#    #+#             */
/*   Updated: 2023/02/24 14:42:21 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_expand(t_list **lst, t_env *env)
{
	t_element	*element;
	t_env_node	*str;

	element = (*lst)->first;
	while (element)
	{
		if (element->type == ENV && element->state != IN_QUOTE)
		{
			str = (search_by_key(env->first, (element->content) + 1));
			if (str != NULL)
			{
				free(element->content);
				element->content = ft_strdup(str->value);
			}
		}
		element = element->next;
	}
}
