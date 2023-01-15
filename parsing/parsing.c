/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:21 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:40:22 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fill_cmd_scmd(t_p_cmd *tmp, t_list **token)
{
	t_list	*next;

	while (token_flag(*token) == CMD_SCMD)
	{
		next = (*token)->next;
		if (tok_struct(*token)->flag & TOKEN_REDIR)
		{
			if (heredoc_parse(*token) == ERROR)
				return (ERROR);
			ft_lstadd_back(&(tmp->l_redir), *token);
		}
		else if (tok_struct(*token)->flag & TOKEN_REDIR_FILE)
		{
			ft_lstadd_back(&(tmp->l_redir), *token);
		}
		else
			ft_lstadd_back(&(tmp->l_argv), *token);
		(*token)->next = NULL;
		*token = next;
	}
	return (0);
}

t_list	*create_fill_cmd(int type, t_list **token)
{
	t_p_cmd		*tmp;
	t_list		*p_cmd;

	tmp = malloc(sizeof(t_p_cmd));
	if (tmp == NULL)
		return (NULL);
	tmp->type = type;
	tmp->l_argv = NULL;
	tmp->l_redir = NULL;
	p_cmd = ft_lstnew(tmp);
	if (p_cmd == NULL)
	{
		p_cmd_destroy(tmp);
		return (NULL);
	}
	p_cmd->next = NULL;
	if (fill_cmd_scmd(p_cmd_struct(p_cmd), token) == ERROR)
	{	
		ft_lstclear(&p_cmd, m_cmd_destroy);
		p_cmd = NULL;
		return (NULL);
	}
	return (p_cmd);
}

t_list	*parsing(t_list *token)
{
	t_list	*cmd;
	t_list	*lst;
	t_list	*next;

	cmd = NULL;
	while (token != NULL)
	{
		lst = create_fill_cmd(token_flag(token), &token);
		if (lst == NULL)
		{
			ft_lstclear(&cmd, m_cmd_destroy);
			return (NULL);
		}
		if (p_cmd_struct(lst)->type != CMD_SCMD)
		{
			next = token->next;
			ft_lstdelone(token, c_token_destroy);
			token = next;
		}
		ft_lstadd_back(&cmd, lst);
	}
	if (cmd == NULL)
		return (NULL);
	parser_pipe_merge(&cmd);
	return (cmd);
}
