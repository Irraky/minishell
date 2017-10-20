/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_protec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/17 15:13:18 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 15:16:25 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**check_env(char **env, const char *key, const char *def_val)
{
	char *value;

	value = env_read(env, key);
	if (value == NULL)
	{
		env = env_write(env, key, def_val);
		return (env);
	}
	free(value);
	return (env);
}

char			**env_protec(char **env)
{
	char	host[14];
	int		fd;
	char	*pwd;

	if ((fd = open("/etc/salt/minion_id", O_RDONLY)) < 0 ||
			read(fd, host, 13) < 0)
		host[0] = '\0';
	env = check_env(env, "HOSTTYPE", "unknown");
	env = check_env(env, "VENDOR", "apple");
	env = check_env(env, "OSTYPE", "darwin");
	env = check_env(env, "MACHTYPE", "x86_64");
	env = check_env(env, "SHLVL", "1");
	env = check_env(env, "PWD", "/Users/drecours");
	env = check_env(env, "LOGNAME", "drecours");
	env = check_env(env, "USER", "drecours");
	env = check_env(env, "GROUP", "2016_paris");
	pwd = env_read(env, "PWD");
	chdir(pwd);
	free(pwd);
	if (host[0] != '\0')
		env = check_env(env, "HOST", host);
	else
		env = check_env(env, "HOST", "unknown");
	return (env);
}
