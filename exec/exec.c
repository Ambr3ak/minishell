/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:46:40 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:46:42 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_s_cmd(t_data *env, char **cmd)
{
	int	pid;
	int	status;
	int	errno;

	init_exec_signals();
	errno = 0;
	pid = fork();
	last_pid_set(pid);
	if (pid == 0)
	{
		status = execve(cmd[0], cmd, g_env);
		if (status == ERROR)
		{
			print_error(MINISHELL, NULL, strerror(errno));
			exit_child(env, NULL, 127);
		}
	}
	status = wait_one_pid(pid);
	last_pid_set(0);
	return (status);
}

int	perform_scmd(t_list *redir)
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
		else if (tok_struct(redir_tmp)->flag == REDIR_HEREDOC)
			status = redir_heredoc(redir_tmp);
		if (status != 0)
			break ;
		redir_tmp = redir_tmp->next;
	}
	return (status);
}

void	restore_fds(t_red_fds *fds)
{
	errno = 0;
	if (fds->in != -1 && fds->out != -1)
	{
		dup2(fds->in, STDIN_FILENO);
		if (errno == 0)
			dup2(fds->out, STDOUT_FILENO);
		if (errno != 0)
			print_error(MINISHELL, NULL, strerror(errno));
		fds->in = -1;
		fds->out = -1;
	}
	free(fds);
}

int	return_status(t_data *env, int status, char **token)
{
	restore_fds(env->fds);
	free_d_char(token);
	if (status == 999)
	{
		exec_last_return_set(exec_last_ruturn_get());
		return (999);
	}
	return (status);
}

int	exec_scmd(t_list *scmd, t_data *env)
{
	char	**token;
	int		status;

	status = 0;
	if (expander(p_cmd_struct(scmd)->l_argv,
			p_cmd_struct(scmd)->l_redir) == -10)
		return (print_error(MINISHELL, "expander:", "failed to expand"));
	if (redir_process(p_cmd_struct(scmd)->l_redir, env->fds) == ERROR)
	{
		free(env->fds);
		return (ERROR);
	}
	token = token_to_array(&env->argc, p_cmd_struct(scmd)->l_argv);
	if ((token || token[0]) && is_builtin(token[0]))
		status = exec_builtin(token, env);
	else
	{
		status = get_path(env, token);
		if (status == 0)
			status = exec_s_cmd(env, token);
		else if (status == 127)
			print_error(MINISHELL, token[0], CMD_NOT_FOUND);
	}
	return (return_status(env, status, token));
}
