/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:17:57 by drecours          #+#    #+#             */
/*   Updated: 2017/10/17 21:30:44 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_compter_mots(char const *str, char c)
{
	int		i;
	int		mots;

	mots = 0;
	i = 0;
	if (str[i] != c && str[i] != '\t')
		++mots;
	i++;
	while (str[i] && str[i] != '\0')
	{
		if ((str[i - 1] == c && str[i - 2] != '\\') || str[i - 1] == '\t')
			mots++;
		i++;
	}
	return (mots);
}

static char		*ft_strsub(char const *s, unsigned int start, size_t size)
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

static int		ft_taille(char const *str, int i, char c)
{
	int		sheep;

	sheep = 0;
	while (str[i] && ((str[i] != c && str[i] != '\t') ||
				((str[i] == c) && str[i - 1] == '\\')))
	{
		i++;
		sheep++;
	}
	return (sheep);
}

char			**ft_splitspaces(char const *str)
{
	char		**tab;
	int			i;
	int			j;

	j = 0;
	if (!str)
		return (NULL);
	i = ft_compter_mots(str, ' ');
	if (!i || !(tab = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (str[i])
		{
			tab[j] = ft_strsub(str, i, ft_taille(str, i, ' '));
			i = i + ft_taille(str, i, ' ');
			j++;
		}
	}
	tab[j] = NULL;
	return (tab);
}
