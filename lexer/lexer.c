/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:59:45 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:38:48 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*tok_struct(t_list *token)
{
	return ((t_cmd *)token->content);
}

int	check_redirection(t_list **c_token)
{
	if ((*c_token)->next == NULL
		|| tok_struct((*c_token)->next)->flag == TOKEN_REDIR)
		return (ERROR);
	if (tok_struct((*c_token)->next)->flag == TOKEN_TEXT
		|| tok_struct((*c_token)->next)->flag == TOKEN_S_QUOTE
		|| tok_struct((*c_token)->next)->flag == TOKEN_D_QUOTE)
		tok_struct((*c_token)->next)->flag |= TOKEN_REDIR_FILE;
	while (tok_struct((*c_token)->next)->flag & TOKEN_CONNECTED)
	{
		tok_struct((*c_token)->next)->flag |= TOKEN_REDIR_FILE;
		(*c_token) = (*c_token)->next;
	}
	return (0);
}

int	check_pipe_red(t_list *token)
{
	t_list	*c_token;

	c_token = token;
	if (c_token && tok_struct(c_token)->flag == TOKEN_PIPE)
		return (print_error(MINISHELL, NULL, ERROR_PIPE));
	while (c_token)
	{
		if (tok_struct(c_token)->flag == TOKEN_PIPE)
		{
			if (c_token->next == NULL
				|| (tok_struct(c_token->next)->flag != TOKEN_REDIR
					&& tok_struct(c_token->next)->flag != TOKEN_TEXT))
				return (print_error(MINISHELL, NULL, ERROR_PIPE));
		}
		if (c_token->next != NULL && tok_struct(c_token)->flag == TOKEN_REDIR
			&& (tok_struct(c_token->next)->flag == TOKEN_PIPE))
			return (print_error(MINISHELL, NULL, ERROR_PIPE));
		else if (tok_struct(c_token)->flag == TOKEN_REDIR)
		{
			if (check_redirection(&c_token) == ERROR)
				return (print_error(MINISHELL, NULL, ERROR_REDIR));
		}
		c_token = c_token->next;
	}
	return (0);
}

t_list	*check_syntax(t_list *token)
{
	if (check_pipe_red(token) == ERROR)
	{
		ft_lstclear(&token, c_token_destroy);
		exec_last_return_set(2);
		return (NULL);
	}
	return (token);
}

t_list	*lexer(char *cmd_input)
{
	t_list	*g_token;
	int		i;

	i = 0;
	g_token = NULL;
	while (cmd_input && cmd_input[i])
	{
		if (redir_token(cmd_input, &g_token, &i) == ERROR)
			break ;
		if (pipe_token(cmd_input, &g_token, &i) == ERROR)
			break ;
		if (text_token(cmd_input, &g_token, &i) == ERROR)
			break ;
		if (quote_token(cmd_input, &g_token, &i) == ERROR)
			break ;
		while (cmd_input[i] && ft_strchr(WHITE_SPACE, cmd_input[i]))
			i++;
	}
	if (cmd_input[i] != '\0')
		ft_lstclear(&g_token, c_token_destroy);
	return (g_token);
}
