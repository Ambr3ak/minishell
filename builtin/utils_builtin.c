/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:30:55 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:30:57 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort(char **g_env)
{
	char	*tmp;
	int		i;
	int		j;
	int		size;

	i = 0;
	size = ft_d_strlen(g_env);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(g_env[i], g_env[j]) > 0)
			{
				tmp = g_env[j];
				g_env[j] = g_env[i];
				g_env[i] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	size_alloc(char **s, int index)
{
	int	str_size;

	str_size = ft_d_strlen(s);
	if (index != -1)
		return (str_size);
	return (str_size + 1);
}
