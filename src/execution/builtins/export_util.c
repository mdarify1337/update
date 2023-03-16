/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:41:57 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 16:42:17 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*ft_remove_char(char	*str, char c)
{
	char	*str1;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	str1 = calloc(ft_strlen(str), 1);
	if (!str1)
		return (NULL);
	while (*str)
	{
		if (*str != c)
			str1[i++] = *str;
		str++;
	}
	return (str1);
}

void	export_with_join(t_env **env, char *arg, int i, t_env_node *node_)
{
	t_env_node	*node;

	node = (*env)->first;
	if (!node)
		insert_to_tail(env, env_new(ft_remove_char(arg, '+')));
	else if (i != -1 && search_by_key(node, ft_substr(arg, 0, i - 1)) != NULL)
	{
		node_ = search_by_key(node, ft_substr(arg, 0, i - 1));
		if (node_)
			node_->value = ft_strjoin_free(node_->value, \
			ft_substr(arg, i + 1, ft_strlen(arg) - i));
	}
	else if (search_by_key(node, arg) == NULL)
		insert_to_tail(env, env_new(ft_remove_char(arg, '+')));
}