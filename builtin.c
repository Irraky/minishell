/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:15:04 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 15:48:41 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_builtin(char **env, t_command *command, int *exec)
{
	if (ft_strlen(command->bin_path) > 0)
	{
		*exec = 1;
		return (env);
	}
	if ((*exec = ft_strcmp(command->bin_name, "setenv")) == 0)
		return (builtin_setenv(env, command));
	if ((*exec = ft_strcmp(command->bin_name, "unsetenv")) == 0)
		return (builtin_unsetenv(env, command));
	if ((*exec = ft_strcmp(command->bin_name, "env")) == 0)
		return (builtin_env(env, command));
	if ((*exec = ft_strcmp(command->bin_name, "cd")) == 0)
		return (builtin_cd(env, command));
	if ((*exec = ft_strcmp(command->bin_name, "echo")) == 0)
		return (builtin_echo(env, command));
	if (ft_strcmp(command->bin_name, "exit") == 0)
		return (builtin_exit(env, command, exec));
	if (ft_strcmp(command->bin_name, "42") == 0)
		return (builtin_42(env));
	*exec = 1;
	return (env);
}
