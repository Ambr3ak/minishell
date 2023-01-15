/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:30:28 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:30:29 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_env_char(char c)
{
	if (ft_isalnum(c))
		return (1);
	if (c == '+')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	can_export(char *export_name)
{
	int	i;

	i = 0;
	if (export_name[0] == '\0' || !ft_isalpha(export_name[0])
		|| export_name[0] == '-')
		return (0);
	while (export_name[i] && export_name[i] != '='
		&& is_env_char(export_name[i]))
		i++;
	if (export_name[i] == '\0' || export_name[i] == '=')
		return (1);
	else
		return (0);
}

int	export_plus_equal(char *var)
{
	int		len;
	char	*name;
	int		ret;

	ret = 0;
	if (var == NULL)
		return (0);
	name = ft_strchr(var, '=');
	if (!name)
		return (0);
	*name = '\0';
	len = ft_strlen(var);
	if (var[len - 1] == '+')
		ret = 1;
	*name = '=';
	return (ret);
}

void	export_process(char **argv, int i)
{
	if (export_plus_equal(argv[i]))
	{
		join_old_var(argv[i], &g_env);
	}
	else if (ft_strchr(argv[i], '='))
		add_char(&g_env, argv[i]);
}

int	export(char **argv, t_data *env)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (env->argc == 1)
		print_env(g_env);
	else
	{
		while (argv[i])
		{
			if (can_export(argv[i]))
				export_process(argv, i);
			else
			{
				print_error(MINISHELL, argv[i], "Identifiant non valable");
				status = 1;
			}
			i++;
		}
	}
	return (status);
}
