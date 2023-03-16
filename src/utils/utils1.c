/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:07:44 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 08:35:23 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	if (c == '\0')
		return (ft_strlen(s));
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 - *s2);
}

char	*ft_strdup(char *str)
{
	char	*str2;
	int		i;

	i = -1;
	str2 = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!str2)
		return (NULL);
	while (str[++i])
		str2[i] = str[i];
	str2[i] = '\0';
	return (str2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*resulttab;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	resulttab = malloc(sizeof(char) * (size + 1));
	if (!resulttab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		resulttab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		resulttab[i++] = s2[j++];
	resulttab[i] = '\0';
	return (resulttab);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*resulttab;
	size_t	size;
	size_t	i;
	size_t	j;

	size = ft_strlen(s1) + ft_strlen(s2);
	resulttab = malloc(sizeof(char) * (size + 1));
	if (!resulttab)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		resulttab[i++] = s1[j++];
	j = 0;
	while (s2[j])
		resulttab[i++] = s2[j++];
	resulttab[i] = '\0';
	free(s1);
	return (resulttab);
}
