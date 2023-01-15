/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:39:50 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:39:56 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_out_app(t_list *redir)
{
	int		fd_out;
	char	*outfile;

	if (redir->next == NULL)
		return (print_error(MINISHELL, NULL, ERROR_CD_2));
	outfile = tok_struct(redir->next)->tk;
	if (ft_strlen(outfile) == 0)
		return (print_error(MINISHELL, NULL, " bad outfile\n"));
	fd_out = open(outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (errno != 0)
	{
		print_error(MINISHELL, outfile, strerror(errno));
		errno = 0;
		return (ERROR);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	redir_out(t_list *redir)
{
	int		fd_out;
	char	*outfile;

	if (redir->next == NULL)
		return (print_error(MINISHELL, NULL, ERROR_CD_2));
	outfile = tok_struct(redir->next)->tk;
	if (ft_strlen(outfile) == 0)
		return (print_error(MINISHELL, NULL, " bad outfile\n"));
	fd_out = open(outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (errno != 0)
	{
		print_error(MINISHELL, outfile, strerror(errno));
		errno = 0;
		return (ERROR);
	}
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (0);
}

int	redir_in(t_list *redir)
{
	int		fd_in;
	char	*infile;

	if (redir->next == NULL)
		return (print_error(MINISHELL, NULL, ERROR_CD_2));
	infile = tok_struct(redir->next)->tk;
	if (ft_strlen(infile) == 0)
		return (print_error(MINISHELL, NULL, " bad infile\n"));
	fd_in = open(infile, O_RDONLY);
	if (errno != 0)
	{
		print_error(MINISHELL, NULL, strerror(errno));
		errno = 0;
		return (ERROR);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	return (0);
}

int	redir_heredoc(t_list *redir)
{
	int		p[2];
	pid_t	pid;
	char	*file;

	if (redir->next == NULL)
		return (ERROR);
	file = tok_struct(redir->next)->tk;
	pipe(p);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		write(p[1], file, ft_strlen(file));
		close(p[1]);
		exit(0);
	}
	else
	{
		close(p[1]);
		dup2(p[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

int	redir_process(t_list *redir, t_red_fds *fds)
{
	int	status;

	if (redir == NULL)
		return (0);
	status = 0;
	fds->in = -1;
	fds->out = -1;
	fds->in = dup(STDIN_FILENO);
	errno = 0;
	if (!errno)
	{
		fds->out = dup(STDOUT_FILENO);
		if (!errno)
			status = perform_scmd(redir);
	}
	else
		status = print_error(MINISHELL, NULL, strerror(errno));
	return (status);
}
