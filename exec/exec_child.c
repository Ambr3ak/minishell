/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:44:49 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:44:51 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dup_fd(t_rec *r, int *fds, int fd_in)
{
	if (r->i != 0)
		dup2(fd_in, STDIN_FILENO);
	if ((r->i + 1) != r->counter)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	close(fd_in);
}

void	exit_child(t_data *env, char *cmd_arr, int status)
{
	if (cmd_arr != NULL)
		print_error(MINISHELL, cmd_arr, CMD_NOT_FOUND);
	free_d_char(g_env);
	free(env->fds);
	free(env);
	exit(status);
}

int	child(int *fds, t_list **l_element, char ***cmd, t_data *env)
{
	t_rec	*child;
	int		status;

	status = 0;
	child = env->r;
	child->id[child->i] = fork();
	last_pid_set(child->id[child->i]);
	if (child->id[child->i] < 0)
		return (2);
	if (child->id[child->i] == 0)
	{
		dup_fd(child, fds, env->fd_in);
		perform_heredoc(p_cmd_struct(*l_element)->l_redir);
		if (perform_redir(p_cmd_struct((*l_element))->l_redir) == ERROR)
			exit_child(env, NULL, 0);
		if (child->can_exec[child->i] != 0)
			exit_child(env, cmd[child->i][0], 127);
		if (is_builtin(cmd[child->i][0]))
			exit_child(env, NULL, exec_builtin(cmd[child->i], env));
		else if (cmd[child->i][0])
			status = execve(cmd[child->i][0], cmd[child->i], g_env);
		perror(cmd[child->i][0]);
	}
	*l_element = (*l_element)->next;
	return (status);
}
