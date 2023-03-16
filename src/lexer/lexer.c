/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 16:58:12 by mmounaji          #+#    #+#             */
/*   Updated: 2023/03/16 12:03:06 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	tokenize(t_element *tokens, char *line, int i, enum e_state *state)
// {
// 	if (in_charset(line[i]) == 0)
// 	{
// 		printf("no null");
// 		i += get_word(tokens, line + i, *state);
// 	}
// 	return (i);
// }
/*
t_list	*flexer_linked(char *line)
{
	t_list			*tokens;
	enum e_state	state;
	int				l;

	l = 0;
	state = GENERAL;
	tokens = NULL;
	//tokens = init_tokens(tokens);
	if (line[l] == '>' || line[l] == '<')
		l += tokenize_redir(tokens, line, l, &state);
	else if (line[l] == '|')
		ft_lstadd_back(&tokens, ft_lstnew(line + (l++), 1, PIPE_LINE, state));
	else if (line[l] == '\'')
		quotes_state(tokens, line + (l++), &state, QOUTE);
	else if (line[l] == '\"')
		quotes_state(tokens, line + (l++), &state, DOUBLE_QUOTE);
	else if (ft_isspace(line[l]) && state != GENERAL)
		ft_lstadd_back(&tokens, ft_lstnew(line + (l++), 1, WHITE_SPACE, state));
	return (tokens);
}
*/

t_list	*lexer(char *line)
{
	int				i;
	t_list			*tokens;
	enum e_state	state;

	i = 0;
	state = GENERAL;
	tokens = NULL;
	tokens = init_tokens(tokens);
	while (line[i])
	{
		if (in_charset(line[i]) == 0)
		{
			i += get_word(tokens, line + i, state);
		}
		else if (line[i] == '$')
		{
			if (in_charset(line[i + 1]) || line[i + 1] == '=')
			{
				ft_lstadd_back(&tokens, ft_lstnew(line + i, 1, WORD, state));
				i++;
			}
			else
				i += get_env_var(tokens, line + i, state);
		}
		else if (line[i] == '>' || line[i] == '<')
			i += tokenize_redir(tokens, line, i, &state);
		else if (line[i] == '|')
			ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, PIPE_LINE, state));
		else if (line[i] == '\'')
		{
			if (line[i + 1] == '\'')
				ft_lstadd_back(&tokens, ft_lstnew("", 1, WORD, IN_QUOTE));
			quotes_state(tokens, line + (i++), &state, QOUTE);
		}
		else if (line[i] == '\"')
		{
			if (line[i + 1] == '\"')
				ft_lstadd_back(&tokens, ft_lstnew("", 1, WORD, IN_DQUOTE));
			quotes_state(tokens, line + (i++), &state, DOUBLE_QUOTE);
		}
		else if (ft_isspace(line[i]) && state != GENERAL)
			ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, WHITE_SPACE, state));
		else
			i++;
	}
	free(line);
	return (tokens);
}

// else if (line[i] == '>' || line[i] == '<')
// 	i += tokenize_redir(tokens, line, i, &state);
// else if (line[i] == '|')
// 	ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, PIPE_LINE,
//			state));
// else if (line[i] == '\'')
// 	quotes_state(tokens, line + (i++), &state, QOUTE);
// else if (line[i] == '\"')
// 	quotes_state(tokens, line + (i++), &state, DOUBLE_QUOTE);
// else if (ft_isspace(line[i]) && state != GENERAL)
// 	ft_lstadd_back(&tokens, ft_lstnew(line + (i++), 1, WHITE_SPACE,
//				state));