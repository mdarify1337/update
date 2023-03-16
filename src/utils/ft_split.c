/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounaji <mmounaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:27:25 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/10 11:00:40 by mmounaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	word_count(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			count++;
			while (*str && *str != c)
				str++;
		}
	}
	return (count);
}

static int	word_len(const char *s, char c)
{	
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s != c && *s)
	{
		count ++;
		s++;
	}
	return (count);
}

static char	*tab_make(char *s, char c)
{
	int		wo_len;
	char	*tab;
	int		i;

	i = 0;
	wo_len = word_len(s, c);
	tab = malloc(sizeof(char) * (wo_len + 1));
	if (!tab)
		return (NULL);
	while (s[i] && i < wo_len)
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	int		i3;
	int		i2;
	char	**result;

	i2 = 0;
	result = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	while (*s)
	{
		i3 = 0;
		while (*s && *s == c)
			s++;
		if (*s)
		{
			result[i2] = tab_make((char *)s, c);
			i2++;
		}
		while (*s && *s != c)
			s++;
	}
	result[i2] = 0;
	return (result);
}
