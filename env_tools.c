/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:17:10 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 16:33:03 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_key(char *env_v)
{
	char	*key;
	size_t	i;

	i = 0;
	while (env_v[i] != '=' && env_v[i] != '\0')
		++i;
	if (!(key = malloc((i + 1) * sizeof(char))))
		return (NULL);
	key[i] = '\0';
	while (i != 0)
	{
		--i;
		key[i] = env_v[i];
	}
	return (key);
}

char	*env_val(char *env_v)
{
	char	*key;
	size_t	i;
	size_t	size;

	i = 0;
	while (env_v[i] != '=' && env_v[i] != '\0')
		++i;
	size = i++;
	while (env_v[size] != '\0')
		++size;
	if (!(key = malloc((size - i + 1) * sizeof(char))))
		return (NULL);
	size -= i;
	key[size] = '\0';
	while (size != 0)
	{
		--size;
		key[size] = env_v[size + i];
	}
	return (key);
}

char	**env_error(char **new_env, char *str)
{
	char	*key;
	char	*tmp;

	if (str[0] == '=')
	{
		env_free(new_env);
		new_env = NULL;
		write(STDERR_FILENO, "env: setenv ", 12);
		write(STDERR_FILENO, str, ft_strlen(str));
		write(STDERR_FILENO, ": Invalid argument\n", 19);
		return (NULL);
	}
	else
	{
		key = ft_strchr(str, '=') + 1;
		tmp = env_key(str);
		new_env = env_write(new_env, tmp, key);
		free(tmp);
	}
	return (new_env);
}

char	**setenv_error(char **env)
{
	write(STDERR_FILENO, "setenv: Variable name must contain ", 35);
	write(STDERR_FILENO, "alphanumeric characters.\n", 25);
	return (env);
}
