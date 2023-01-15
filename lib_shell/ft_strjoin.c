/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:30:37 by abourdar          #+#    #+#             */
/*   Updated: 2020/11/30 18:53:09 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_buff(char *s1, char c)
{
	size_t	i;
	char	*new;

	i = 0;
	if (!s1)
		return (NULL);
	new = malloc((ft_strlen(s1) + 2) * sizeof(char));
	if (new != NULL)
	{
		while (s1[i])
		{
			new[i] = s1[i];
			i++;
		}
		new[i] = c;
		new[i + 1] = '\0';
	}
	free(s1);
	return (new);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	while (s1[j])
		dest[i++] = s1[j++];
	j = 0;
	while (s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}
