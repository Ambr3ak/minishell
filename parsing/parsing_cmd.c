/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:40:40 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:40:41 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_m_cmd	*cmd_struct(t_list *cmd)
{
	return ((t_m_cmd *)cmd->content);
}

int	m_cmd_type(t_list *cmd)
{
	return (*(int *)(cmd->content));
}

t_p_cmd	*p_cmd_struct(t_list *p_cmd)
{
	return ((t_p_cmd *)p_cmd->content);
}

int	token_flag(t_list *token)
{
	if (token == NULL)
		return (ERROR);
	else if (tok_struct(token)->flag & TOKEN_PIPE)
		return (CMD_PIPE);
	else if (tok_struct(token)->flag & (TOKEN_TEXT | TOKEN_D_QUOTE
			| TOKEN_S_QUOTE | TOKEN_REDIR | TOKEN_REDIR_FILE | TOKEN_CONNECTED))
		return (CMD_SCMD);
	return (ERROR);
}
