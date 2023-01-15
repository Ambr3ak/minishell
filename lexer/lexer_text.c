/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:39:10 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:39:24 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*liste_add_token(char *text, int type)
{
	t_list	*token;
	t_cmd	*s_token;

	s_token = malloc(sizeof(t_cmd));
	token = NULL;
	if (s_token)
	{
		s_token->tk = text;
		s_token->flag = type;
		token = ft_lstnew(s_token);
	}
	if (!token)
		return (NULL);
	token->next = NULL;
	return (token);
}

int	text_token(char *input, t_list **token, int *i)
{
	int		size;
	char	*tk;
	t_list	*l_token;

	size = size_txt(input + (*i));
	if (size > 0)
	{
		tk = ft_substr(input, *i, size);
		if (!tk)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		l_token = liste_add_token(tk, TOKEN_TEXT);
		if (!l_token)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		ft_lstadd_back(token, l_token);
		(*i) += size;
		if (!ft_strchr(WHITE_SPACE, input[*i]) && is_other(&input[*i]) == 0)
			tok_struct(l_token)->flag |= TOKEN_CONNECTED;
	}
	return (0);
}

int	quote_token(char *input, t_list **token, int *i)
{
	int		size;
	char	*tk;
	t_list	*l_token;

	size = size_quote(input + (*i));
	if (size == -2)
		return (ERROR);
	if (size > 0)
	{
		tk = ft_substr(input, *i + 1, size - 2);
		if (input[*i] == '\'')
			l_token = liste_add_token(tk, TOKEN_S_QUOTE);
		else
			l_token = liste_add_token(tk, TOKEN_D_QUOTE);
		ft_lstadd_back(token, l_token);
		(*i) += size;
		if (!ft_strchr(WHITE_SPACE, input[*i]) && is_other(&input[*i]) == 0)
			tok_struct(l_token)->flag |= TOKEN_CONNECTED;
	}
	return (0);
}
