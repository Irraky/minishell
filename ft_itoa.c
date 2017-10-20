/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 04:15:21 by drecours          #+#    #+#             */
/*   Updated: 2017/01/04 16:34:24 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_ilen(int n)
{
	int		i;

	if (n < 0)
	{
		i = 1;
		n = -n;
	}
	else
		i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*nb;
	int		i;

	if (n == -2147483647 - 1)
		return (ft_strdup("-2147483648"));
	i = ft_ilen(n);
	if (!(nb = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	if (n < 0 && n != -0)
	{
		nb[0] = '-';
		n = -n;
	}
	if (n == -0 || n == 0 || n == +0)
		nb[0] = '0';
	nb[i] = '\0';
	while (n > 0)
	{
		i--;
		nb[i] = n % 10 + 48;
		n = n / 10;
	}
	return (nb);
}
