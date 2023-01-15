/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:06:54 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:06:56 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(char **declare)
{
	char	**sorted;
	int		i;

	i = 0;
	sorted = malloc(sizeof(char *) * (ft_d_strlen(declare) + 1));
	sorted = ft_memcpy(sorted, declare,
			(sizeof(char *) * (ft_d_strlen(declare) + 1)));
	sort(sorted);
	if (sorted)
	{
		while (sorted[i])
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(sorted[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
		free(sorted);
	}
}

char	*new_export_value(char *tmp, char *new_value)
{
	char	*new;
	char	*tmp2;

	new = ft_strjoin(tmp, "=");
	tmp2 = new;
	new = ft_strjoin(new, new_value);
	free(tmp2);
	return (new);
}

void	join_old_var(char *var_name, char ***g_env)
{
	int		index;
	char	*tmp;
	char	*new_value;
	char	**new_s;
	int		i;

	tmp = find_var(var_name);
	index = find_index_var(tmp);
	new_value = ft_strchr(var_name, '=') + 1;
	new_s = (char **)malloc(sizeof(char *) * (size_alloc(*g_env, index) + 2));
	i = 0;
	while ((*g_env)[i])
	{
		if (i == index)
			new_s[i] = ft_strjoin((*g_env)[i], new_value);
		else
			new_s[i] = ft_strdup((*g_env)[i]);
		i++;
	}
	if (index == -1)
		new_s[i++] = new_export_value(tmp, new_value);
	free(tmp);
	new_s[i] = NULL;
	init_new_pwd(new_s, g_env);
}

void	add_char(char ***s, char *added)
{
	char	**new_s;
	char	*var_to_find;
	int		index;
	int		i;

	var_to_find = find_var(added);
	index = find_index_var(var_to_find);
	free(var_to_find);
	new_s = (char **)malloc(sizeof(char *) * (size_alloc(*s, index) + 2));
	i = 0;
	while ((*s)[i])
	{
		if (i == index)
			new_s[i] = ft_strdup(added);
		else
			new_s[i] = ft_strdup((*s)[i]);
		i++;
	}
	if (index == -1)
		new_s[i++] = ft_strdup(added);
	new_s[i] = NULL;
	init_new_pwd(new_s, s);
}

char	*get_env_value_1(char *env_name, int *status)
{
	int		i;
	int		name_size;
	char	*tmp;

	i = 0;
	if (init_value(&env_name, &tmp, &name_size) == ERROR)
		return (NULL);
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
	*status = 0;
	return (tmp);
}
