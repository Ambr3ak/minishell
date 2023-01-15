/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 10:29:00 by abourdar          #+#    #+#             */
/*   Updated: 2020/11/25 11:07:18 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup( char *s1)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = ft_strlen(s1);
	dest = malloc((size + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
