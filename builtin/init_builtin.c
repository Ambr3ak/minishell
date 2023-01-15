/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:30:35 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:30:36 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pwd(char **new_pwd, char **old_pwd, char ***new_env, char **s)
{
	*new_pwd = malloc(sizeof(char) * 4096);
	*new_env = (char **)malloc(sizeof(char *) * (ft_d_strlen(s) + 1));
	*old_pwd = ft_strjoin("OLDPWD=", get_env_value(ft_strdup("PWD")));
	getcwd(*new_pwd, 4096);
}

void	init_new_pwd(char **new_env, char ***s)
{
	free_d_char(*s);
	(*s) = NULL;
	(*s) = new_env;
}
