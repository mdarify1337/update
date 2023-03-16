/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:34:27 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 10:50:56 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	flinked_send_error(int l, char *command)
{
	if (l == 1)
	{
		ft_putstr_fd("MINISHELL: ERROR 3--->: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("----command not found-----\n", 2);
		exit(127);
	}
	if (l == 2)
	{
		ft_putstr_fd("MINISHELL: ERROR 4--->: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("---- No such file or directory ----\n", 2);
		exit(127);
	}
}

int	fcalcule_size(t_cmd_node *command)
{
	t_cmd_node	*minishell;
	int			l;

	l = 0;
	minishell = command;
	while (minishell)
	{
		minishell = minishell->next;
		l++;
	}
	return (l);
}
