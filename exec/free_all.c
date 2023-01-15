/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:45:24 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:26 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_path(char *cp, char *tmp, t_data *env)
{
	int	i;

	i = 0;
	if (env->path_i == 1)
	{
		while (env->path[i])
		{
			free(env->path[i++]);
		}
		free(env->path);
	}
	if (!env->absolut_path)
	{
		free(tmp);
		free(cp);
	}
}

void	f_t_char(char ***s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free_d_char(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	free_d_char(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != NULL)
		{
			free(s[i]);
			s[i] = NULL;
		}
		i++;
	}
	free(s);
	s = NULL;
}

void	free_cmd(char ***cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free_d_char(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_env(t_data *env)
{	
	if (env->r->can_exec)
	{
		free(env->r->can_exec);
		env->r->can_exec = NULL;
	}
	if (env->r->can_exec)
	{
		free(env->r->can_exec);
		env->r->can_exec = NULL;
	}
	if (env->r->id)
	{
		free(env->r->id);
		env->r->id = NULL;
	}
	if (env->r->fd)
	{
		free(env->r->fd);
		env->r->fd = NULL;
	}
	if (env->r)
	{
		free(env->r);
		env->r = NULL;
	}
}
