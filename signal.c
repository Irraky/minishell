/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:06:09 by drecours          #+#    #+#             */
/*   Updated: 2017/10/18 13:45:50 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		segv_signal(int signal)
{
	(void)signal;
	write(STDERR_FILENO, "Segfault error.\n", 16);
	exit(SIGSEGV);
}

static void		noth_signal(int signal)
{
	(void)signal;
}

static void		c_signal(int signal)
{
	(void)signal;
	write(STDOUT_FILENO, "\n<", 2);
	if (g_usr)
		write(STDOUT_FILENO, g_usr, ft_strlen(g_usr));
	write(STDOUT_FILENO, ":", 1);
	if (g_pwd)
		write(STDOUT_FILENO, g_pwd, ft_strlen(g_pwd));
	write(STDOUT_FILENO, "$>", 3);
}

void			get_signal(void)
{
	signal(SIGSEGV, segv_signal);
	signal(SIGINT, c_signal);
	signal(SIGTSTP, noth_signal);
	signal(SIGQUIT, noth_signal);
}
