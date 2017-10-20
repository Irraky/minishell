/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:15:26 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 17:38:18 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			fix_root(char *path)
{
	if (ft_strlen(path) == 0)
		path_subcpy("/", path, 0, 1);
	return (0);
}

static char	**cd_home(char **env, t_command *cmd)
{
	int		old_argc;
	char	**old_argv;
	char	**cd_return;

	old_argc = cmd->argc;
	old_argv = cmd->argv;
	cmd->argv = malloc(sizeof(char*) * 3);
	cmd->argv[0] = old_argv[0];
	cmd->argv[1] = ft_strdup("~");
	cmd->argv[2] = NULL;
	cmd->argc = 2;
	cd_return = builtin_cd(env, cmd);
	free(cmd->argv[1]);
	free(cmd->argv);
	cmd->argv = old_argv;
	cmd->argc = old_argc;
	return (cd_return);
}

char		**builtin_cd(char **env, t_command *cmd)
{
	char	*pwd;

	if (cmd->argc < 2)
		return (cd_home(env, cmd));
	if (cmd->argc > 2)
		return (cd_error(env, -3, NULL, cmd));
	if (cmd->argv[1][0] == '-')
		return (cd_minus(env, cmd));
	if (!(pwd = env_read(env, "PWD")))
		return (env);
	return (ft_path(pwd, cmd, env));
}

char		**builtin_echo(char **env, t_command *command)
{
	int i;
	int	flag;

	i = 1;
	flag = 0;
	if (command->argc > 1 && !ft_strcmp(command->argv[i], "-n"))
		i++;
	while (i < command->argc && command->argv[i] != NULL)
	{
		if (flag == 1)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, command->argv[i], ft_strlen(command->argv[i]));
		++i;
		flag = 1;
	}
	if (!command->argv[1] || ft_strcmp(command->argv[1], "-n"))
		write(STDOUT_FILENO, "\n", 1);
	return (env);
}

char		**builtin_exit(char **env, t_command *command, int *exec)
{
	int		i;
	int		flag;

	i = 0;
	flag = 1;
	if (command->argc == 2)
	{
		flag = 0;
		if (command->argv[1][0] == '-')
			i++;
		while (command->argv[1][i])
		{
			if (!(command->argv[1][i] >= '0' && command->argv[1][i] <= '9'))
				flag = 1;
			i++;
		}
	}
	if (flag == 0 || command->argc == 1)
	{
		*exec = BUILTIN_EXIT;
		return (env);
	}
	write(STDERR_FILENO, EX_SYNTAX, sizeof(EX_SYNTAX));
	*exec = -1;
	return (env);
}
