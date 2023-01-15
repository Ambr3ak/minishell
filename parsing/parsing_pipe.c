/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:41:14 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:41:15 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	clean_pipe(t_m_cmd *lst, t_list *start, t_list *end)
{
	t_list	*next;
	t_list	*iter;

	iter = start;
	while (iter != end->next)
	{
		next = iter->next;
		if (cmd_struct(iter)->type == CMD_PIPE)
			ft_lstdelone(iter, m_cmd_destroy);
		else if (cmd_struct(iter)->type == CMD_PIPELINE)
		{
			ft_lstadd_back(&(lst->l_element), cmd_struct(iter)->l_element);
			cmd_struct(iter)->l_element = NULL;
			ft_lstdelone(iter, m_cmd_destroy);
		}
		else
		{
			ft_lstadd_back(&(lst->l_element), iter);
			if (iter != end)
				iter->next = NULL;
		}
		iter = next;
	}
	end->next = NULL;
}

static t_list	*pipe_end(t_list *pipe)
{
	t_list	*iter;

	iter = pipe;
	while (iter)
	{
		if ((cmd_struct(iter)->type & (CMD_SCMD | CMD_PIPELINE))
			&& iter->next && cmd_struct(iter->next)->type == CMD_PIPE
			&& iter->next->next && (cmd_struct(iter->next->next)->type
				& (CMD_SCMD | CMD_PIPELINE)))
		{
			iter = iter->next->next;
		}
		else
			return (iter);
	}
	return (NULL);
}

static t_list	*pipe_start(t_list *cmd)
{
	t_list	*iter;

	iter = cmd;
	while (iter)
	{
		if ((cmd_struct(iter)->type & (CMD_SCMD | CMD_PIPELINE))
			&& iter->next && cmd_struct(iter->next)->type == CMD_PIPE
			&& iter->next->next && (cmd_struct(iter->next->next)->type
				& (CMD_SCMD | CMD_PIPELINE)))
		{
			return (iter);
		}
		iter = iter->next;
	}
	return (NULL);
}

int	parser_pipe_merge(t_list **cmd)
{
	int		i;
	t_list	*pipe;
	t_list	*start;
	t_list	*end;

	i = 1;
	while (i > 0)
	{
		start = pipe_start(*cmd);
		end = pipe_end(start);
		if (!start || !end)
			return (0);
		pipe = create_m_cmd(CMD_PIPELINE);
		if (pipe == NULL)
		{
			ft_lstclear(cmd, p_cmd_destroy);
			return (ERROR);
		}
		lst_relink(cmd, pipe, start, end);
		clean_pipe(cmd_struct(pipe), start, end);
		i = 1;
	}
	return (0);
}
