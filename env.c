/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:17:01 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 14:02:57 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**env_dup(char **env)
{
	size_t			i;
	char			**new_env;
	extern char		**environ;

	i = 0;
	if (env == NULL)
		env = environ;
	while (environ[i] != NULL)
		++i;
	if (!((new_env = (char**)malloc((i + 1) * sizeof(char*)))))
		return (NULL);
	i = 0;
	while (environ[i] != NULL)
	{
		new_env[i] = ft_strdup(environ[i]);
		++i;
	}
	new_env[i] = NULL;
	new_env = env_protec(new_env);
	return (new_env);
}

int		env_free(char **env)
{
	size_t		i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		++i;
	}
	free(env);
	return (0);
}

char	*env_read(char **env, const char *key)
{
	size_t	i;
	char	*env_k;

	i = 0;
	while (env[i] != NULL)
	{
		env_k = env_key(env[i]);
		if (ft_strcmp(env_k, key) == 0)
		{
			free(env_k);
			return (env_val(env[i]));
		}
		free(env_k);
		++i;
	}
	return (NULL);
}

char	**env_add(char **env, const char *env_val)
{
	size_t	i;
	char	**new_env;

	i = 0;
	while (env[i] != NULL)
		++i;
	if (!(new_env = malloc((i + 2) * sizeof(char*))))
	{
		write(STDERR_FILENO, "Malloc error.\n", 14);
		return (env);
	}
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = env[i];
		++i;
	}
	new_env[i] = ft_strdup(env_val);
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

char	**env_write(char **env, const char *key, const char *val)
{
	size_t	i;
	char	*new_env;
	char	*tmp_env;

	tmp_env = ft_strjoin(key, "=");
	new_env = ft_strjoin(tmp_env, val);
	free(tmp_env);
	i = 0;
	while (env[i] != NULL)
	{
		tmp_env = env_key(env[i]);
		if (ft_strcmp(tmp_env, key) == 0)
		{
			free(tmp_env);
			free(env[i]);
			env[i] = new_env;
			return (env);
		}
		free(tmp_env);
		++i;
	}
	env = env_add(env, new_env);
	free(new_env);
	return (env);
}
