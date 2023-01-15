/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:44:55 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:00 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_absolut_path(t_data *env, char *cmd)
{
	env->path_i = 0;
	if (is_builtin(cmd))
		return (0);
	if (access(cmd, F_OK) == 0)
	{
		env->path_i = 1;
		return (0);
	}
	return (127);
}

int	check_status(int *status, t_data *env, char **cmd)
{
	if (ft_strcmp(cmd[0], ".") == 0)
	{
		free_d_char(env->path);
		print_error(MINISHELL, NULL, "nom de fichier nécessaire en argument");
		return (*status = 2);
	}
	if (ft_strcmp(cmd[0], "..") == 0)
	{
		free_d_char(env->path);
		return (*status = 127);
	}
	if (*status == ABSOLUT_PATH)
		return (*status = get_absolut_path(env, cmd[0]));
	if (*status == SCRIPT)
		return (*status = 0);
	if (*status == ERROR)
		return (*status = 127);
	else
		return (1);
}

int	init_bin(t_data *env, char **cmd, char *cp, char *tmp)
{
	env->path_i = 1;
	free(*cmd);
	*cmd = ft_strdup(cp);
	free_path(cp, tmp, env);
	return (0);
}

int	get_path(t_data *env, char **cmd)
{
	int		i;
	char	*tmp;
	char	*cp;
	int		status;

	i = 0;
	if (!cmd)
		return (0);
	if (!cmd[0])
		return (127);
	status = init_path(env, cmd[0]);
	if (check_status(&status, env, cmd) != 1)
		return (status);
	while (env->path && env->path_i == 0 && env->path[i])
	{
		tmp = ft_strjoin("/", *cmd);
		cp = ft_strjoin(env->path[i], tmp);
		if (access(cp, F_OK) == 0)
			return (init_bin(env, &cmd[0], cp, tmp));
		free_path(cp, tmp, env);
		i++;
	}
	free_d_char(env->path);
	return (127);
}
