/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:45:05 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:07 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_pid_status(t_rec *r, int status, t_red_fds *fds)
{
	if (status == 999)
		wait_pid(r, r->counter);
	else
		status = wait_pid(r, r->counter);
	last_pid_set(0);
	restore_fds(fds);
	return (status);
}

int	starting_process(t_list *l_element, char ***cmd, t_data *env)
{
	int			status;
	t_rec		*r;
	t_red_fds	*fds;
	int			fd_in_out[2];

	status = 0;
	fds = init_std();
	if (!fds)
		return (print_error(MINISHELL, NULL, strerror(errno)));
	r = env->r;
	r->i = 0;
	env->fd_in = dup(STDIN_FILENO);
	while (r->i < r->counter)
	{
		pipe(fd_in_out);
		status = child(fd_in_out, &l_element, cmd, env);
		dup2(fd_in_out[0], env->fd_in);
		close(fd_in_out[0]);
		close(fd_in_out[1]);
		r->i++;
	}
	close(env->fd_in);
	return (wait_pid_status(r, status, fds));
}

int	exec_pipe(t_list *cmd, t_data *env)
{
	char	***cmd_arr;
	int		i;
	int		status;

	env->r = NULL;
	env->r = init_process(counter(cmd), env->r);
	cmd_arr = init_pipe_cmd(cmd_struct(cmd)->l_element, env->r->counter);
	i = 0;
	while (cmd_arr[i])
	{
		env->path_i = 0;
		status = get_path(env, cmd_arr[i]);
		env->r->can_exec[i] = status;
		i++;
	}
	i = starting_process(cmd_struct(cmd)->l_element, cmd_arr, env);
	free_env(env);
	f_t_char(cmd_arr);
	restore_fds(env->fds);
	return (i);
}
