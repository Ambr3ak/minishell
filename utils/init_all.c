/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:36:52 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:36:53 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_cmd(char **s)
{
	(*s) = malloc(sizeof(char) * (INPUT_MAX + 1));
}

int	init_size(t_list *scmd, int *argc)
{
	int	size;

	size = lst_size(scmd);
	*argc = size;
	return (size);
}

int	init_path(t_data *env, char *cmd)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	if ((cmd && cmd[0] == '/') || (cmd && cmd[0] == '.'
			&& cmd[1] == '/') || is_builtin(cmd))
		return (ABSOLUT_PATH);
	if ((cmd && cmd[0] && cmd[1]) && (cmd[0] == '.' && cmd[1] == '/'))
		return (SCRIPT);
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], "PATH=", 5))
		{
			env->path = ft_split(g_env[i] + 5, ':');
			check++;
		}
		i++;
	}
	if (!check)
		return (ERROR);
	return (0);
}

void	init_exec_signals(void)
{
	signal(SIGINT, exec_ctrl_c_handle);
	signal(SIGQUIT, sigquit_handler);
}

int	init_value(char **env_name, char **tmp, int *name_size)
{
	(*tmp) = ft_strdup("\0");
	(*env_name) = ft_strjoin_buff((*env_name), '=');
	if (!(*env_name))
	{
		free(*tmp);
		return (ERROR);
	}
	*name_size = ft_strlen((*env_name));
	return (0);
}
