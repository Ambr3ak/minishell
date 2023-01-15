/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:40:11 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 10:06:48 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_str(char **var, char *tk)
{
	char	*env_var;
	char	*tmp;
	int		status;
	int		i;

	if (!tk)
		return (NULL);
	tmp = *var;
	i = 0;
	while (tk[i] == '$')
		i++;
	env_var = ft_strdup("");
	while (tk[i] && (ft_isalnum(tk[i]) || tk[i] == '_'))
	{
		env_var = ft_strjoin_buff(env_var, tk[i]);
		i++;
	}
	status = unexisted_var(env_var);
	env_var = get_env_value_1(env_var, &status);
	*var = ft_strjoin(*var, env_var);
	free(tmp);
	if (status == 0)
		free(env_var);
	return (*var);
}

int	get_value(t_cmd *token, int	*i, char **var)
{
	if (token->tk[*i] == '$' && token->tk[*i + 1] == '?')
	{
		expand_str_exit_code(var);
		(*i)++;
	}
	else if ((token->tk[*i] == '$' && token->tk[*i + 1] == '\0'
			&& (token->flag & TOKEN_CONNECTED)))
		return (0);
	else if (token->tk[*i] == '$' && (ft_isalnum(token->tk[*i + 1])
			|| token->tk[*i + 1] == ' ' || token->tk[*i + 1] == '_'))
	{
		if (!expand_str(var, &(token->tk[*i])))
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		while (ft_isalnum(token->tk[*i + 1]) || token->tk[*i + 1] == '_')
			(*i)++;
	}
	else
		*var = ft_strjoin_buff(*var, token->tk[*i]);
	if (!(*var))
		return (print_error(MINISHELL, NULL, ERROR_MEMORY));
	return (0);
}

int	check_expand(t_cmd *token)
{
	char	*expand_var;
	int		i;

	i = 0;
	if (!token->tk || (token->flag == TOKEN_S_QUOTE)
		|| !ft_strchr(token->tk, '$') || ((token->tk[0] == '$'
				&& !token->tk[1]) && (!(token->flag & TOKEN_CONNECTED)
				|| (token->flag & TOKEN_D_QUOTE))))
		return (0);
	expand_var = ft_strdup("");
	if (!expand_var)
		return (print_error(MINISHELL, NULL, ERROR_MEMORY));
	while (token->tk[i])
	{
		if (get_value(token, &i, &expand_var) == -10)
		{
			free(expand_var);
			return (-10);
		}
		i++;
	}
	free(token->tk);
	token->tk = ft_strdup(expand_var);
	free(expand_var);
	return (0);
}

int	token_expand(t_list *cmd)
{
	t_list	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (check_expand(tok_struct(tmp)) == -10)
			return (-10);
		tmp = tmp->next;
	}
	return (0);
}

int	expander(t_list *argv, t_list *redir)
{
	int	check;

	check = 0;
	if (argv)
		check = token_expand(argv);
	if (redir && check != ERROR)
		check = token_expand(redir);
	return (check);
}
