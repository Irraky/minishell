/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:20:15 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 13:47:36 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strtrim(char const *s)
{
	int				i;
	int				j;
	int				k;
	char			*copie;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == '\t' || s[i] == ' ' || s[i] == '\n')
		i++;
	j = ft_strlen(s) - 1;
	while ((s[j] == '\t' || s[j] == ' ' || s[j] == '\n') && i < j)
		j--;
	if (!(copie = (char *)malloc(j - i + 2)))
		return (NULL);
	k = -1;
	while (++k <= j - i)
		copie[k] = s[i + k];
	copie[k] = '\0';
	return (copie);
}

size_t		path_trim(char *path, size_t size)
{
	char	*trimmed_str;
	size_t	len;

	trimmed_str = ft_strtrim(path);
	if (trimmed_str == NULL)
		return (0);
	len = ft_strlen(trimmed_str);
	path_subcpy(trimmed_str, path, 0, len < size ? len : size);
	free(trimmed_str);
	return (len);
}

size_t		path_subcpy(const char *source, char *dest,
			size_t start, size_t len)
{
	size_t		i;

	i = start;
	while (i < start + len)
	{
		dest[i - start] = source[i];
		++i;
	}
	dest[i - start] = '\0';
	return (i - start);
}

char		*path_join(const char *path, const char *bin)
{
	char	*path_part;
	char	*path_full;
	size_t	path_size;

	path_size = ft_strlen(path);
	if (path[path_size] != '/')
		path_part = ft_strjoin(path, "/");
	else
		path_part = ft_strdup(path);
	path_full = ft_strjoin(path_part, bin);
	free(path_part);
	return (path_full);
}
