/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:30:48 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:30:49 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_char(char ***s, int index)
{
	char	**new_s;
	int		j;
	int		l;

	j = 0;
	l = 0;
	new_s = malloc(sizeof(char *) * ((ft_d_strlen(*s) - 1) + 1));
	while ((*s)[l])
	{
		if (l != index)
		{
			new_s[j] = ft_strdup((*s)[l]);
			j++;
		}
		l++;
	}
	new_s[j] = NULL;
	init_new_pwd(new_s, s);
}

void	unset_env_var(char *env_var, t_data *env)
{
	int	i;
	int	name_size;
	int	index_unset;

	i = 0;
	name_size = ft_strlen(env_var);
	i = 0;
	index_unset = -1;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], env_var, name_size))
			index_unset = i;
		i++;
	}
	if (index_unset != -1)
	{
		delete_char(&g_env, index_unset);
		env->env_size = ft_d_strlen(g_env);
	}
}

int	unset(char **argv, t_data *env)
{
	int	i;
	int	j;
	int	exit;

	i = 1;
	j = 0;
	exit = 0;
	if (!argv[1])
		return (0);
	while (argv[i])
	{
		j = 0;
		while (ft_isalnum(argv[i][j]))
			j++;
		if (argv[i][0] == '\0' || argv[i][j] != '\0')
		{
			print_error(MINISHELL, argv[i], ERROR_UNSET);
			exit = 1;
		}
		else
			unset_env_var(argv[i], env);
		i++;
	}
	return (exit);
}
