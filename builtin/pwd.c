/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:30:40 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:30:43 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(void)
{
	char	*pwd;

	pwd = get_env_value(ft_strdup("PWD"));
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
