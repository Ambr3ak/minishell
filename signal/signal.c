/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:39:08 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:39:10 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	wait_one_pid(int pid)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit from keyboard \n", STDERR_FILENO);
		else if (WTERMSIG(status) == SIGINT)
			status = 128 + WTERMSIG(status);
	}
	return (status);
}

void	sigquit_handler(int signal_value)
{
	if (last_pid_get() != 0)
	{
		kill(last_pid_get(), signal_value);
	}
}

void	ctrl_c_herdoc_handle(int signal)
{
	if (signal == SIGINT)
	{
		exec_last_return_set(130);
		close(STDIN_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	ctrl_c_handle(int signal)
{
	if (signal == SIGINT)
	{
		exec_last_return_set(130);
		ft_putchar_fd('\n', STDERR_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	exec_ctrl_c_handle(int signal_value)
{
	if (signal_value == SIGINT)
	{
		exec_last_return_set(130);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}
