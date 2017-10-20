/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:19:14 by drecours          #+#    #+#             */
/*   Updated: 2017/10/10 17:11:15 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_compter_mots(char const *str, char c)
{
	int		i;
	int		mots;

	mots = 0;
	i = 0;
	if (str[i] != c)
		++mots;
	i++;
	while (str[i])
	{
		if (str[i - 1] == c)
			mots++;
		i++;
	}
	return (mots);
}

static char			*ft_strsub(char const *s, unsigned int start, size_t size)
{
	char	*troncon;
	size_t	i;

	i = -1;
	if (!s)
		return (NULL);
	if (!(troncon = (char*)malloc(sizeof(char) * size + 1)))
		return (NULL);
	while (++i < size)
		troncon[i] = s[start + i];
	troncon[i] = '\0';
	return (troncon);
}

static int			ft_taille(char const *str, int i, char c)
{
	int		sheep;

	sheep = 0;
	while (str[i] != c && str[i])
	{
		i++;
		sheep++;
	}
	return (sheep);
}

char				**ft_strsplit(char const *str, char c)
{
	char		**tab;
	int			i;
	int			j;

	j = 0;
	if (!str)
		return (NULL);
	i = ft_compter_mots(str, c);
	if (!i || !(tab = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i])
		{
			tab[j] = ft_strsub(str, i, ft_taille(str, i, c));
			i = i + ft_taille(str, i, c);
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
