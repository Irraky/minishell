/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 12:50:59 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 17:36:53 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		alph_num(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] <= '9' && str[i] >= '0') || (str[i] <= 'z' &&
						str[i] >= 'a') || (str[i] <= 'Z' && str[i] >= 'A') ||
					str[i] == ':' || str[i] == '/' || str[i] == '.' ||
					str[i] == '_' || str[i] == '-'))
			break ;
		++i;
	}
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	**cd_error(char **env, int err, char *str, t_command *command)
{
	if (str)
		free(str);
	if (command->argc == 2)
		write(STDERR_FILENO, command->argv[1], ft_strlen(command->argv[1]));
	if (err == -1)
		write(STDERR_FILENO, CD_NOT_FOUND, sizeof(CD_NOT_FOUND));
	if (err == -2)
		write(STDERR_FILENO, CD_NO_RIGHT, sizeof(CD_NO_RIGHT));
	if (err == -3)
		write(STDERR_FILENO, CD_TOO_MANY, sizeof(CD_TOO_MANY));
	if (err == -4)
		write(STDERR_FILENO, STAT_ERROR, sizeof(STAT_ERROR));
	if (err == -5)
		write(STDERR_FILENO, CD_NOT_DIR, sizeof(CD_NOT_DIR));
	return (env);
}

char	**test_env(t_command *command, char **env, int *i)
{
	char	**new_env;

	if (ft_strcmp(command->argv[*i], "-i") == 0)
	{
		if (!(new_env = (char**)malloc(sizeof(char*) * 1)))
		{
			write(STDERR_FILENO, "Malloc error.\n", 14);
			return (NULL);
		}
		*i = *i + 1;
		new_env[0] = NULL;
	}
	else
		new_env = env_dup(env);
	*i = *i - 1;
	return (new_env);
}

char	**manage_env(t_command *command, char **env, int i)
{
	char	**new_env;
	char	*tmp;
	int		j;

	if (!(new_env = (char**)malloc(sizeof(char*) * i)))
	{
		write(STDERR_FILENO, "Malloc error.\n", 14);
		return (env);
	}
	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		tmp = env_key(env[i]);
		if (!(ft_strcmp(tmp, command->argv[1]) == 0))
		{
			new_env[j] = ft_strdup(env[i]);
			j++;
		}
		++i;
		free(tmp);
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**ft_path(char *pwd, t_command *cmd, char **env)
{
	char	path[PATH_MAX];
	char	*tmp_path;

	if (cmd->argv[1][0] == '/')
		path_subcpy(cmd->argv[1], path, 0, ft_strlen(cmd->argv[1]));
	else
	{
		tmp_path = path_join(pwd, cmd->argv[1]);
		path_subcpy(tmp_path, path, 0, ft_strlen(tmp_path));
		free(tmp_path);
	}
	path_eval(path);
	resolve_relative_path(env, path);
	if (fix_root(path) == 0 && dir_exists(path) != 0)
		return (cd_error(env, dir_exists(path), pwd, cmd));
	env = env_write(env, "OLDPWD", pwd);
	env = env_write(env, "PWD", path);
	chdir(path);
	free(pwd);
	return (env);
}
