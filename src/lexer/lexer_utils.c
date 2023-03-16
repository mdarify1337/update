/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:08:56 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 12:03:58 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_word(t_list *tokens, char *str, enum e_state state)
{
	int	i;

	i = 0;
	while (in_charset(str[i]) == 0)
		i++;
	ft_lstadd_back(&tokens, ft_lstnew(str, i, WORD, state));
	return (i);
}

void	quotes_state(t_list *tokens, char *str, enum e_state *state, enum e_token state2)
{
	enum e_state	e_state;
	enum e_token	e_type;

	if (state2 == QOUTE)
	{
		e_state = IN_QUOTE;
		e_type = QOUTE;
	}
	else
	{
		e_state = IN_DQUOTE;
		e_type = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		ft_lstadd_back(&tokens, ft_lstnew(str, 1, e_type, *state));
		*state = e_state;
	}
	else if (*state == e_state)
	{
		*state = GENERAL;
		ft_lstadd_back(&tokens, ft_lstnew(str, 1, e_type, *state));
	}
	else
		ft_lstadd_back(&tokens, ft_lstnew(str, 1, e_type, *state));
}

int	tokenize_redir(t_list *tokens, char *str, int i, enum e_state *state)
{
	int	j;

	j = i;
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			ft_lstadd_back(&tokens, ft_lstnew(str + (i++), 2, HERE_DOC, *state));
		else
			ft_lstadd_back(&tokens, ft_lstnew(str + i, 1, REDIR_IN, *state));
		i++;
	}
	else if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			ft_lstadd_back(&tokens, ft_lstnew(str + (i++), 2, DREDIR_OUT, *state));
		else
			ft_lstadd_back(&tokens, ft_lstnew(str + i, 1, REDIR_OUT, *state));
		i++;
	}
	return (i - j);
}

int	get_env_var(t_list *tokens, char *str, enum e_state state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while ((str[i] == '_' || is_alphanum(str[i]) == 1) && str[i] != '\n' && str[i] != '\0')
			i++;
	ft_lstadd_back(&tokens, ft_lstnew(str, i, ENV, state));
	return (i);
}
