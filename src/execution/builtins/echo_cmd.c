/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:23:48 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 11:22:34 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	some_ns(char *s)
{
	int	i;

	if (!s)
		return (0);
	if (s[0] != '-')
		return (0);
	i = 1;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **s)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (*s == NULL)
	{
		printf("\n");
		return ;
	}
	while (some_ns(s[++i]))
		flag = 1;
	i--;
	while (s[++i])
	{
		if (ft_strcmp(s[i], "$?") == 0)
			printf("%lld", g_fcode.exit_status);
		else
			printf("%s", s[i]);
	}
	if (!flag)
		printf("\n");
	g_fcode.exit_status = 0;
}
