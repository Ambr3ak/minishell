/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:06:48 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:06:50 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_concat(char *var)
{
	char	*new;
	int		i;

	i = 0;
	while (var[i] && var[i] != '+')
		i++;
	if (var[i] == '\0')
		return (NULL);
	new = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (var[i] && var[i] != '+')
	{
		new[i] = var[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*find_var(char *var)
{
	int		i;
	char	*new;

	i = 0;
	if (!var)
		return (NULL);
	if (export_plus_equal(var))
		return (find_concat(var));
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '\0')
		return (NULL);
	new = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (var[i] && var[i] != '=')
	{
		new[i] = var[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	find_index_var(char *var_name)
{
	int	i;
	int	name_size;
	int	index_var;

	i = 0;
	name_size = ft_strlen(var_name);
	i = 0;
	index_var = -1;
	while (g_env[i])
	{
		if (!ft_strncmp(var_name, g_env[i], name_size)
			&& g_env[i][name_size] == '=')
			index_var = i;
		i++;
	}
	return (index_var);
}

char	*get_env_value(char *env_name)
{
	int		i;
	int		name_size;
	char	*tmp;

	i = 0;
	tmp = ft_strdup("\0");
	env_name = ft_strjoin_buff(env_name, '=');
	if (!env_name)
	{
		free(tmp);
		return (NULL);
	}
	name_size = ft_strlen(env_name);
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], env_name, name_size))
		{
			free(env_name);
			free(tmp);
			return (ft_strchr(g_env[i], '=') + 1);
		}
		i++;
	}
	free(env_name);
	return (tmp);
}

char	**get_env(t_data *env, char **envp)
{
	int		i;
	char	**g_env;

	i = 0;
	while (envp[i])
		i++;
	env->env_size = i;
	g_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (g_env)
	{
		i = 0;
		while (envp[i])
		{
			g_env[i] = ft_strdup(envp[i]);
			if (g_env[i] == NULL)
				return (NULL);
			i++;
		}
		g_env[i] = NULL;
		return (g_env);
	}
	return (NULL);
}
