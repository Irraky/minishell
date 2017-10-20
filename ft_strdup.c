/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:18:17 by drecours          #+#    #+#             */
/*   Updated: 2017/10/10 17:30:26 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int			i;
	int			len;
	char		*truc;

	i = 0;
	len = ft_strlen(s1);
	if (!(truc = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i != len)
	{
		truc[i] = s1[i];
		++i;
	}
	truc[len] = '\0';
	return (truc);
}
