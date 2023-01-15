/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Gkatounk <gkatounk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:25:45 by Gkatounk          #+#    #+#             */
/*   Updated: 2020/12/10 15:25:48 by Gkatounk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*calc(int n, int count, char *str)
{
	unsigned int	sinal;

	str[count] = 0;
	count--;
	if (n > 0)
		sinal = n;
	else
		sinal = -n;
	while (sinal)
	{
		str[count] = (sinal % 10) + '0';
		sinal /= 10;
		count--;
	}
	if (!count)
		str[count] = '-';
	return (str);
}

float	f_ternaire(float cond, float a, float b)
{
	if (cond)
		return (a);
	return (b);
}

char	*ft_itoa(int n)
{
	int				count;
	unsigned int	sinal;
	char			*str;

	count = f_ternaire((n > 0), 0, 1);
	sinal = f_ternaire((n > 0), n, -n);
	if (n == 0)
	{
		str = malloc(count + 1);
		if (!(str))
			return (NULL);
		str[0] = '0';
		str[1] = 0;
		return (str);
	}
	while (sinal)
	{
		count++;
		sinal /= 10;
	}
	str = malloc(count + 1);
	if (!(str))
		return (NULL);
	return (calc(n, count, str));
}
