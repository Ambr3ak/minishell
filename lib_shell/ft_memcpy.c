/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:26:09 by abourdar          #+#    #+#             */
/*   Updated: 2020/11/25 11:05:47 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int				i;
	unsigned char	*str;
	unsigned char	*source;

	i = 0;
	str = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (n == 0)
		return (str);
	if (!(dest) && !(src))
		return (dest);
	while (i < (int)n)
	{
		str[i] = source[i];
		i++;
	}
	return (str);
}
