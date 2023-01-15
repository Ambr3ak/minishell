/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_pid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:39:41 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:39:42 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	select_redir(char *redir)
{
	if (ft_strcmp(redir, "<") == 0)
		return (REDIR_IN);
	if (ft_strcmp(redir, "<<") == 0)
		return (REDIR_HEREDOC);
	if (ft_strcmp(redir, ">") == 0)
		return (REDIR_OUT);
	if (ft_strcmp(redir, ">>") == 0)
		return (REDIR_OUT_APP);
	return (0);
}

int	perform_heredoc(t_list *redir)
{
	t_list	*redir_tmp;
	int		status;

	status = 0;
	redir_tmp = redir;
	while (redir_tmp)
	{
		tok_struct(redir_tmp)->flag = select_redir(tok_struct(redir_tmp)->tk);
		if (tok_struct(redir_tmp)->flag == REDIR_HEREDOC)
			status = redir_heredoc(redir_tmp);
		if (status != 0)
			break ;
		redir_tmp = redir_tmp->next;
	}
	return (status);
}

int	perform_pipe(t_list *redir)
{
	t_list	*redir_tmp;
	int		status;

	status = 0;
	redir_tmp = redir;
	while (redir_tmp)
	{
		tok_struct(redir_tmp)->flag = select_redir(tok_struct(redir_tmp)->tk);
		if (tok_struct(redir_tmp)->flag == REDIR_OUT)
			status = redir_out(redir_tmp);
		else if (tok_struct(redir_tmp)->flag == REDIR_IN)
			status = redir_in(redir_tmp);
		else if (tok_struct(redir_tmp)->flag == REDIR_OUT_APP)
			status = redir_out_app(redir_tmp);
		if (status != 0)
			break ;
		redir_tmp = redir_tmp->next;
	}
	return (status);
}

int	perform_redir(t_list *redir)
{
	int	status;

	status = perform_pipe(redir);
	return (status);
}

int	wait_pid(t_rec *recup, int count)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < count)
	{
		waitpid(recup->id[i], &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGQUIT)
				ft_putstr_fd("Quit from keyboard \n", STDERR_FILENO);
			else if (WTERMSIG(status) == SIGINT)
				status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (status);
}
