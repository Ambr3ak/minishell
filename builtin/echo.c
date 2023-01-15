/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:29:51 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:29:52 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_line_arg(char *arg)
{
	int	i;

	i = 0;
	if (arg == NULL || arg[0] != '-')
		return (1);
	i++;
	while (arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (0);
	return (1);
}

int	echo(char **cmd, int argc)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (cmd[i] && new_line_arg(cmd[i]) == 0)
		i++;
	if (i == 1)
		nl++;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (i < argc - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
