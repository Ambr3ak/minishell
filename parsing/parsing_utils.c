/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:41:22 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:41:23 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*create_m_cmd(int type)
{
	t_m_cmd	*m_cmd;
	t_list	*cmd;

	m_cmd = malloc(sizeof(t_m_cmd));
	if (m_cmd == NULL)
		return (NULL);
	m_cmd->type = type;
	m_cmd->l_element = NULL;
	cmd = ft_lstnew(m_cmd);
	if (cmd == NULL)
	{
		m_cmd_destroy(m_cmd);
		return (NULL);
	}
	cmd->next = NULL;
	return (cmd);
}

char	*token_to_str(t_list *token)
{
	char	*str;
	char	*tmp;

	if (token == NULL || tok_struct(token)->tk == NULL)
		return (NULL);
	str = ft_strdup(tok_struct(token)->tk);
	while (token && (tok_struct(token)->flag & TOKEN_CONNECTED))
	{
		tmp = str;
		str = ft_strjoin(str, tok_struct(token->next)->tk);
		free(tmp);
		if (str == NULL)
			return (NULL);
		token = token->next;
	}
	return (str);
}

void	m_cmd_destroy(void *m_cmd)
{
	if (((t_m_cmd *)m_cmd)->type == CMD_SCMD)
		p_cmd_destroy(m_cmd);
	else
	{
		if (((t_m_cmd *)m_cmd)->l_element)
			ft_lstclear(&(((t_m_cmd *)m_cmd)->l_element), m_cmd_destroy);
		free(m_cmd);
	}
}

void	c_token_destroy(void *token)
{
	if (((t_cmd *)token)->tk != NULL)
	{
		if (((t_cmd *)token)->tk)
		{
			free(((t_cmd *)token)->tk);
			((t_cmd *)token)->tk = NULL;
		}
		if (token)
		{
			free(token);
			token = NULL;
		}
	}
}

void	p_cmd_destroy(void *tmp)
{
	if (((t_p_cmd *)tmp)->l_argv != NULL)
	{
		ft_lstclear(&(((t_p_cmd *)tmp)->l_argv), c_token_destroy);
		((t_p_cmd *)tmp)->l_argv = NULL;
	}
	if (((t_p_cmd *)tmp)->l_redir)
	{
		ft_lstclear(&(((t_p_cmd *)tmp)->l_redir), c_token_destroy);
		((t_p_cmd *)tmp)->l_redir = NULL;
	}
	free(tmp);
	tmp = NULL;
}
