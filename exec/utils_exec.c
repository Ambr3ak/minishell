/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:45:40 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:43 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter(t_list *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = cmd_struct(cmd)->l_element;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**pipe_to_array(t_list *argv)
{
	int	size;

	size = lst_size(argv);
	return (token_to_array(&size, argv));
}

char	***init_pipe_cmd(t_list *l_element, int count)
{
	int		i;
	char	***cmd;
	t_list	*tmp;

	cmd = malloc(sizeof(char **) * (count + 1));
	if (!cmd)
		return (NULL);
	tmp = l_element;
	i = 0;
	while (tmp)
	{
		if (expander(p_cmd_struct(tmp)->l_argv,
				p_cmd_struct(tmp)->l_redir) == -10)
			print_error(MINISHELL, "expander:", "failed to expand");
		cmd[i] = pipe_to_array(p_cmd_struct(tmp)->l_argv);
		tmp = tmp->next;
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_rec	*init_process(int count, t_rec *r)
{
	r = malloc(sizeof(t_rec));
	r->counter = count;
	r->fd = malloc(sizeof(int *) * (count - 1));
	r->id = malloc(sizeof(int) * count);
	r->can_exec = malloc(sizeof(int) * count);
	return (r);
}

t_red_fds	*init_std(void)
{
	int			status;
	t_red_fds	*fds;

	init_exec_signals();
	fds = malloc(sizeof(t_red_fds));
	ft_memset(fds, 0, sizeof(t_red_fds));
	status = 0;
	fds->in = -1;
	fds->out = -1;
	fds->in = dup(STDIN_FILENO);
	errno = 0;
	if (!errno)
	{
		fds->out = dup(STDOUT_FILENO);
		if (!errno)
			return (fds);
	}
	else
	{
		print_error(MINISHELL, NULL, strerror(errno));
		return (NULL);
	}
	return (fds);
}
