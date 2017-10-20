/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:15:15 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 16:49:24 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**print_env(char **env)
{
	size_t		i;

	i = 0;
	while (env[i] != NULL)
	{
		write(STDOUT_FILENO, env[i], ft_strlen(env[i]));
		write(STDOUT_FILENO, "\n", 1);
		++i;
	}
	return (env);
}

char			**builtin_setenv(char **env, t_command *command)
{
	if (command->argc > 3)
	{
		write(STDERR_FILENO, "Usage: setenv [KEY value]\n", 27);
		return (env);
	}
	else if (command->argc == 1)
		return (print_env(env));
	if (!(alph_num(command->argv[1])) || (command->argc == 3 &&
				!(alph_num(command->argv[2]))))
		return (setenv_error(env));
	if (command->argc == 3)
		env = env_write(env, command->argv[1], command->argv[2]);
	else
		env = env_write(env, command->argv[1], "");
	return (env);
}

char			**builtin_unsetenv(char **env, t_command *command)
{
	char		**new_env;
	char		*tmp;
	size_t		i;

	i = 0;
	if (command->argc != 2)
	{
		write(STDERR_FILENO, "Usage: unsetenv KEY\n", 20);
		return (env);
	}
	else if ((tmp = env_read(env, command->argv[1])) == NULL)
	{
		write(STDERR_FILENO, "Inexistant key.\n", 16);
		free(tmp);
		return (env);
	}
	else
		free(tmp);
	while (env[i] != NULL)
		++i;
	new_env = manage_env(command, env, i);
	env_free(env);
	return (new_env);
}

char			**builtin_env(char **env, t_command *command)
{
	int		i;
	char	**new_env;

	i = 1;
	if (command->argc == 1)
		return (print_env(env));
	if (!(new_env = test_env(command, env, &i)))
		return (env);
	while (command->argv[++i])
	{
		if ((ft_strchr(command->argv[i], '=')))
		{
			if (!(new_env = env_error(new_env, command->argv[i])))
				return (env);
		}
		else
		{
			exec_cmd(new_env, command);
			env_free(new_env);
			return (env);
		}
	}
	print_env(new_env);
	env_free(new_env);
	return (env);
}
