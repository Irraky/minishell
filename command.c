/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:15:49 by drecours          #+#    #+#             */
/*   Updated: 2017/10/10 16:15:51 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_init(t_command *command)
{
	ft_bzero(command, sizeof(t_command));
	return (0);
}

int		command_free_content(t_command *command)
{
	int i;

	if (command->argc > 0)
	{
		i = 0;
		while (i < command->argc && command->argv[i] != NULL)
		{
			free(command->argv[i]);
			++i;
		}
		free(command->argv);
		command->argv = NULL;
	}
	return (0);
}
