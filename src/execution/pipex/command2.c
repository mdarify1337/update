/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:31:52 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/15 16:23:00 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	flen_linked(char *s)
{
	int	l;

	l = 0;
	while (s[l])
	{
		l++;
	}
	return (l);
}

char	**env_arr(t_env_node *env)
{
	t_env_node	*tmp;
	char		**s;
	int			i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = env;
	s = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (tmp)
	{
		s[i] = ft_strjoin(ft_strjoin(tmp->key, "="), tmp->value);
		tmp = tmp->next;
		i++;
	}
	s[i] = NULL;
	return (s);
}
