/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:39:00 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:39:02 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_token(char *input, t_list **token, int *i)
{
	char	*tk;
	t_list	*l_token;

	if (input[*i] == '|')
	{
		tk = ft_substr(input, *i, 1);
		if (!tk)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		l_token = liste_add_token(tk, TOKEN_PIPE);
		if (!l_token)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		ft_lstadd_back(token, l_token);
		(*i) += 1;
	}
	return (0);
}

int	can_redir(char *s)
{
	if (*s == '>' && *(s + 1) == '<')
		return (ERROR);
	if (*s == '<' && *(s + 1) != '<')
		return (1);
	else if (*s == '<' && *(s + 1) == '<')
		return (1);
	else if (*s == '>' && *(s + 1) != '>')
		return (1);
	else if (*s == '>' && *(s + 1) == '>')
		return (1);
	return (ERROR);
}

int	redir_token(char *input, t_list **token, int *i)
{
	char	*tk;
	t_list	*l_token;
	int		size;

	size = 0;
	if (input[*i] == '>' || input[*i] == '<')
	{
		size++;
		if (can_redir(&input[*i]) == ERROR)
		{
			exec_last_return_set(2);
			return (print_error(MINISHELL, NULL, ERROR_REDIR));
		}
		if (input[*i + 1] == '>' || input[*i + 1] == '<')
			size++;
		tk = ft_substr(input, *i, size);
		if (!tk)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		l_token = liste_add_token(tk, TOKEN_REDIR);
		if (!l_token)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		ft_lstadd_back(token, l_token);
		(*i) += size;
	}
	return (0);
}
