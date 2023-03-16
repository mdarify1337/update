/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:21:55 by mdarify           #+#    #+#             */
/*   Updated: 2023/03/16 11:28:04 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_mlen(char **m)
{
	int	i;

	i = 0;
	if (m && *m)
		while (m[i])
			i++;
	return (i);
}

static int	is_numeric(const char *s)
{
	int	is_numeric;
	int	i;

	is_numeric = 0;
	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i] && ft_isdigit(s[i]))
	{
		is_numeric = 1;
		i++;
	}
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (s[i] != '\0')
		is_numeric = 0;
	return (is_numeric);
}

long long int	ft_atoi_exit(char *str)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (nbr < 0)
	{
		fprint_ecode("minishell: exit: numeric argument required", 2, 255);
		g_fcode.exit_status = 255;
		exit(g_fcode.exit_status);
	}
	return (sign * nbr);
}

int	builtin_exit(char **cmd)
{
	int	size;

	ft_putendl_fd("exit", STDOUT_FILENO);
	size = ft_mlen(cmd);
	if (size == 1)
	{
		exit(g_fcode.exit_status);
	}
	g_fcode.exit_status = ft_atoi_exit(cmd[1]);
	if (size == 2)
	{
		if (!is_numeric(cmd[1]) || ft_atoi_exit(cmd[1]) > 9223372036854775807)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd[1], STDERR_FILENO);
			ft_putendl_fd(": numeric argument required", STDERR_FILENO);
			exit(255);
		}
	}
	if (size == 3)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		g_fcode.exit_status = 1;
	}
	exit(g_fcode.exit_status);
}
