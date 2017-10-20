/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:27:11 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 17:41:58 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**path_error(char **env, char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	return (env);
}

char		**cd_minus(char **env, t_command *cmd)
{
	char	*pwd;
	char	*oldpwd;

	if (cmd->argv[1][1] != '\0')
		write(STDERR_FILENO, CD_USAGE, ft_strlen(CD_USAGE));
	else
	{
		if (!(pwd = env_read(env, "PWD")))
			return (path_error(env, "cd: PWD not found.\n"));
		if (!(oldpwd = env_read(env, "OLDPWD")))
			return (path_error(env, "cd: OLDPWD not set.\n"));
		if (dir_exists(oldpwd) != 0)
			return (cd_error(env, dir_exists(oldpwd), pwd, cmd));
		env = env_write(env, "OLDPWD", pwd);
		env = env_write(env, "PWD", oldpwd);
		chdir(oldpwd);
		free(pwd);
		free(oldpwd);
	}
	return (env);
}
