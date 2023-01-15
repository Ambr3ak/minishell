/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:29:58 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:29:59 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **g_env)
{
	int	i;

	if (!g_env)
	{
		return (print_error(MINISHELL, "env", ERROR_ENV));
	}
	i = 0 ;
	while (i < ft_d_strlen(g_env))
	{
		ft_putstr_fd(g_env[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
	return (0);
}
