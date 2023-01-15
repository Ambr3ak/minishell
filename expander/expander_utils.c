/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:40:17 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:40:19 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del_empty_tok(t_list *cmd)
{
	t_list	*tmp;
	t_list	*lst;
	t_list	*new;

	tmp = cmd;
	new = NULL;
	lst = tmp;
	while (lst)
	{
		if (tok_struct(tmp)->tk[0] != '\0')
			ft_lstadd_back(&new, tmp);
		else
		{
			lst = tmp->next;
			free(tmp);
		}
		tmp = lst;
	}
	cmd = new;
}

int	expand_str_exit_code(char **var)
{
	char	*exit_code;
	char	*tmp;

	tmp = *var;
	exit_code = ft_itoa(exec_last_ruturn_get());
	if (exit_code == NULL)
		return (print_error(MINISHELL, NULL, strerror(ENOMEM)));
	*var = ft_strjoin(*var, exit_code);
	free(tmp);
	free(exit_code);
	if (*var == NULL)
		return (print_error(MINISHELL, NULL, strerror(ENOMEM)));
	return (0);
}

int	unexisted_var(char *env_name)
{
	int	i;

	i = 0;
	while (g_env[i])
	{
		if (!ft_strncmp(g_env[i], env_name, ft_strlen(env_name)))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
