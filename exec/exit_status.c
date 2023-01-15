/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:45:13 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:45:19 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	*exit_last_return(void)
{
	static int	last_return = 0;

	return (&last_return);
}

int	exec_last_ruturn_get(void)
{
	return (*exit_last_return());
}

void	exec_last_return_set(int status)
{
	if (status == ERROR)
		status = EXIT_FAILURE;
	*exit_last_return() = status;
}
