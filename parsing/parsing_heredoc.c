/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:41:05 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:41:06 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*heredoc_readline(char *limiter)
{
	char	*read_str;
	char	*here_str;

	signal(SIGINT, ctrl_c_herdoc_handle);
	here_str = ft_strdup("");
	if (here_str == NULL)
		return (NULL);
	read_str = readline("> ");
	while (read_str && ft_strncmp(read_str, limiter, ft_strlen(limiter) + 1))
	{
		read_str = str_add_chr(read_str, '\n');
		if (read_str == NULL)
		{
			free(here_str);
			print_error(MINISHELL, NULL, strerror(ENOMEM));
			return (NULL);
		}
		here_str = str_add_str(here_str, read_str);
		if (here_str == NULL)
			break ;
		free(read_str);
		read_str = readline("> ");
	}
	free(read_str);
	return (here_str);
}

static int	recup_file(t_list *file, char **limit)
{
	int	fd;

	fd = dup(STDIN_FILENO);
	if (fd == -1)
		return (print_error(MINISHELL, NULL, strerror(errno)));
	free(tok_struct(file)->tk);
	if (isatty(STDIN_FILENO))
		tok_struct(file)->tk = heredoc_readline(*limit);
	if (errno == EBADF)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			print_error(MINISHELL, NULL, strerror(errno));
		close(fd);
		return (ERROR);
	}
	close(fd);
	if (tok_struct(file)->tk == NULL)
		return (print_error(MINISHELL, NULL, strerror(errno)));
	return (0);
}

static void	heredoc_merge(t_list *redir, t_list **token)
{
	t_list	*iter;
	t_list	*tmp;

	if (tok_struct(redir)->flag & TOKEN_CONNECTED)
	{
		tok_struct(redir)->flag &= ~(TOKEN_CONNECTED);
		iter = redir->next;
		while (iter && tok_struct(iter)->flag & TOKEN_CONNECTED)
		{
			if (tok_struct(iter)->flag & TOKEN_S_QUOTE)
				tok_struct(redir)->flag |= TOKEN_S_QUOTE;
			if (tok_struct(iter)->flag & TOKEN_D_QUOTE)
				tok_struct(redir)->flag |= TOKEN_D_QUOTE;
			tmp = iter->next;
			lst_node_remove(token, iter, c_token_destroy);
			iter = tmp;
		}
		if (tok_struct(iter)->flag & TOKEN_S_QUOTE)
			tok_struct(redir)->flag |= TOKEN_S_QUOTE;
		if (tok_struct(iter)->flag & TOKEN_D_QUOTE)
			tok_struct(redir)->flag |= TOKEN_D_QUOTE;
		lst_node_remove(token, iter, c_token_destroy);
	}
}

int	redir_type(char *redir)
{
	int	i;

	if (redir == NULL)
		return (ERROR);
	i = 0;
	while (ft_isdigit(redir[i]))
		i++;
	if (redir[i] == '>' && redir[i + 1] == '\0')
		return (REDIR_OUT);
	else if (redir[i] == '>' && redir[i + 1] == '>')
		return (REDIR_OUT_APP);
	else if (redir[i] == '<' && redir[i + 1] == '\0')
		return (REDIR_IN);
	else if (redir[i] == '<' && redir[i + 1] == '<')
		return (REDIR_HEREDOC);
	else
		return (ERROR);
}

int	heredoc_parse(t_list *token)
{
	t_list	*file;
	char	*limit;

	if (redir_type(tok_struct(token)->tk) == REDIR_HEREDOC)
	{
		file = token->next;
		limit = token_to_str(file);
		if (limit == NULL)
			return (print_error(MINISHELL, NULL, ERROR_HEREDOC));
		if (recup_file(file, &limit) == ERROR)
		{
			free(limit);
			ft_lstclear(&token, c_token_destroy);
			return (ERROR);
		}
		free(limit);
		tok_struct(file)->flag |= TOKEN_HEREDOC;
		heredoc_merge(file, &token);
	}
	return (0);
}
