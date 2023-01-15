/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:45:31 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:33 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*last_pid(void)
{
	static int	last_pid = 0;

	return (&last_pid);
}

int	last_pid_get(void)
{
	return (*last_pid());
}

void	last_pid_set(int i)
{
	*last_pid() = i;
}
