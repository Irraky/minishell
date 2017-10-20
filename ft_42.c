/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   42.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 15:48:01 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 16:09:56 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**builtin_42(char **env)
{
	pid_t	pid;
	int		status;
	char	*(nyan[3]);

	nyan[0] = "/usr/bin/telnet";
	nyan[1] = "nyancat.dakko.us";
	nyan[2] = NULL;
	pid = fork();
	if (pid == 0)
		exit(execve("/usr/bin/telnet", nyan, env));
	else
	{
		waitpid(pid, &status, 0);
		status_error(status);
	}
	return (env);
}
