/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:34:21 by abourdar          #+#    #+#             */
/*   Updated: 2020/11/30 11:43:48 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_str(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int	ft_sstr(char const *s, char c, int i)
{
	int	n;

	n = 0;
	while (s[i])
	{
		if (s[i] != c)
			n++;
		else
			return (n);
		i++;
	}
	return (n);
}

static char	**ft_str_split(char c, int n, char const *s)
{
	int		l;
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	dest = malloc((ft_count_str(s, c) + 1) * sizeof(char *));
	while (j < n && s[i] != '\0')
	{
		l = 0;
		while (s[i] == c)
			i++;
		dest[j] = malloc((ft_sstr(s, c, i) + 1) * sizeof(char));
		while (s[i] != c && s[i] != '\0')
		{
			dest[j][l++] = s[i++];
		}
		dest[j][l] = '\0';
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**dest;
	int		n;

	if (!(s))
		return (0);
	n = ft_count_str(s, c);
	dest = ft_str_split(c, n, s);
	return (dest);
}
