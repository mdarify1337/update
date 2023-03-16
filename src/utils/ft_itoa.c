/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:06:02 by mmounaji          #+#    #+#             */
/*   Updated: 2023/02/27 20:54:14 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	str_size_count(long int n)
{
	int	i;

	i = 2;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*fill_str(char *str, long int n, int len)
{
	int	i;

	i = 0;
	str[len] = '\0';
	len --;
	if (n < 0)
	{
		n *= -1;
		i++;
		str[0] = '-';
	}
	while (len >= i)
	{
		str[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		length;

	length = str_size_count(n);
	str = malloc(sizeof(char) * length);
	if (str != NULL)
		str = fill_str(str, n, length - 1);
	return (str);
}
