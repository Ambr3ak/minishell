/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:25:17 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:25:19 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_builtin(char **token, t_data *env_s)
{
	if (ft_strcmp(token[0], "echo") == 0)
		return (echo(token, env_s->argc));
	if (ft_strcmp(token[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(token[0], "env") == 0)
		return (env(g_env));
	if (ft_strcmp(token[0], "exit") == 0)
		return (999);
	if (ft_strcmp(token[0], "unset") == 0)
		return (unset(token, env_s));
	if (ft_strcmp(token[0], "cd") == 0)
		return (cd(token, env_s->argc));
	if (ft_strcmp(token[0], "export") == 0)
		return (export(token, env_s));
	return (0);
}

char	*is_builtin(char *arr)
{
	if (!arr)
		return (NULL);
	if (ft_strcmp(arr, "echo") == 0)
		return (arr);
	if (ft_strcmp(arr, "cd") == 0)
		return (arr);
	if (ft_strcmp(arr, "pwd") == 0)
		return (arr);
	if (ft_strcmp(arr, "export") == 0)
		return (arr);
	if (ft_strcmp(arr, "unset") == 0)
		return (arr);
	if (ft_strcmp(arr, "env") == 0)
		return (arr);
	if (ft_strcmp(arr, "exit") == 0)
		return (arr);
	return (NULL);
}
