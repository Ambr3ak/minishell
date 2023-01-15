/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:37:20 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:37:21 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*prompt_str(void)
{
	char	*pwd;
	char	*user;
	char	*str;
	char	*str_tmp;

	user = NULL;
	pwd = NULL;
	user = get_env_value(ft_strdup("USER"));
	if (!user)
		user = ft_strdup("");
	pwd = get_env_value(ft_strdup("PWD"));
	if (!pwd)
		pwd = ft_strdup("");
	str = ft_strjoin("\1\033[32;1m\2", user);
	str_tmp = str;
	str = ft_strjoin(str, "\1@:\e[1;34m~\2");
	free(str_tmp);
	str_tmp = str;
	str = ft_strjoin(str, pwd);
	free(str_tmp);
	str_tmp = str;
	str = ft_strjoin(str, "\1\e[0m$ \2");
	free(str_tmp);
	return (str);
}
