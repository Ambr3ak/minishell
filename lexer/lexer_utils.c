/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:39:36 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 09:39:47 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_other(char *s)
{
	if (*s == '<' && *(s + 1) != '<')
		return (1);
	else if (*s == '<' && *(s + 1) == '<')
		return (1);
	else if (*s == '>' && *(s + 1) != '>')
		return (1);
	else if (*s == '>' && *(s + 1) == '>')
		return (1);
	else if (*s == '|')
		return (1);
	return (0);
}

int	size_txt(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(WHITE_SPACE, s[i]))
			break ;
		if (ft_strchr("\'\"", s[i]))
			break ;
		if (is_other(&s[i]))
			break ;
		i++;
	}
	return (i);
}

int	size_quote(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (!s || !ft_strchr("\'\"", s[i]))
		return (-1);
	c = s[i];
	i++;
	while (s[i])
	{
		if (s[i] == c)
			break ;
		i++;
	}
	if (s[i] != c)
	{
		print_error(MINISHELL, NULL, ERROR_QUOTE);
		return (-2);
	}
	return (i + 1);
}
