/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:25:23 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:25:26 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_directory(char **argv, int argc)
{
	char	*dir;

	dir = NULL;
	if (argc == 1)
		dir = get_env_value(ft_strdup("HOME"));
	else if (argv[1])
	{
		if (ft_strncmp(argv[1], "-", 1) == 0)
		{
			dir = get_env_value(ft_strdup("OLDPWD"));
			ft_putstr_fd(dir, 1);
			ft_putchar_fd('\n', 1);
		}
		else
			dir = argv[1];
	}
	return (dir);
}

int	index_var(char *path)
{
	int	i;

	i = 0;
	while (g_env[i] && ft_strncmp(g_env[i], path, ft_strlen(path)) != 0)
	{
		i++;
	}
	return (i);
}

void	change_pwd(char ***s)
{
	char	*new_pwd;
	char	*old_pwd;
	char	**new_env;
	char	*pwd;
	int		i;

	i = 0;
	init_pwd(&new_pwd, &old_pwd, &new_env, *s);
	pwd = ft_strjoin("PWD=", new_pwd);
	while ((*s)[i])
	{
		if (i == index_var("OLDPWD="))
			new_env[i] = ft_strdup(old_pwd);
		else if (i == index_var("PWD="))
			new_env[i] = ft_strdup(pwd);
		else
			new_env[i] = ft_strdup((*s)[i]);
		i++;
	}
	new_env[i] = NULL;
	init_new_pwd(new_env, s);
	free(old_pwd);
	free(new_pwd);
	free(pwd);
}

int	cd(char **argv, int argc)
{
	char	*new_dir;

	if (argc > 2)
	{
		print_error(MINISHELL, "cd", ERROR_CD_1);
		return (1);
	}
	new_dir = get_directory(argv, argc);
	if (new_dir)
	{
		if (chdir(new_dir) == -1)
		{
			print_error(MINISHELL, new_dir, ERROR_CD_2);
			return (1);
		}
		change_pwd(&g_env);
		return (0);
	}
	return (ERROR);
}
