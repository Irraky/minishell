/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shell_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:19:49 by drecours          #+#    #+#             */
/*   Updated: 2017/10/16 15:24:26 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	extract_bin(char *cmd, size_t cmd_size, t_command *command)
{
	size_t		i;
	size_t		j;
	char		bin[PATH_MAX];

	i = 0;
	while (i < cmd_size)
	{
		if ((cmd[i] == ' ' && (cmd[i - 1] != '\\')) || cmd[i] == '\t')
			break ;
		++i;
	}
	path_subcpy(cmd, bin, 0, i);
	j = i;
	while (j > 0)
	{
		if (bin[j] == '/')
		{
			++j;
			break ;
		}
		--j;
	}
	path_subcpy(bin, command->bin_path, 0, j);
	path_subcpy(bin, command->bin_name, j, i - j);
	return (i);
}

static size_t	extract_args(char *cmd, t_command *command)
{
	char		**args;
	size_t		i;

	args = ft_splitspaces(cmd);
	i = 0;
	while (args[i] != NULL)
		++i;
	command->argc = i;
	command->argv = args;
	return (i);
}

int				parse_shell_cmd(char *cmd, size_t cmd_size, t_command *command)
{
	path_trim(cmd, cmd_size);
	extract_bin(cmd, cmd_size, command);
	extract_args(cmd, command);
	return (0);
}
