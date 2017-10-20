/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:19:27 by drecours          #+#    #+#             */
/*   Updated: 2017/10/16 15:18:04 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		prompt_display_path(char **env, char *path)
{
	size_t	len;
	char	*home;

	home = env_read(env, "HOME");
	if (home != NULL)
		len = ft_strlen(home);
	else
		len = 0;
	if (home != NULL && ft_strncmp(home, path, len) == 0)
	{
		write(STDOUT_FILENO, "~", 1);
		write(STDOUT_FILENO, path + len, ft_strlen(path) - len);
	}
	else
		write(STDOUT_FILENO, path, ft_strlen(path));
	if (home != NULL)
		free(home);
}

void			display_prompt(char **env)
{
	char	*pwd;
	char	*user;

	if (g_usr)
		free(g_usr);
	if (g_pwd)
		free(g_pwd);
	pwd = env_read(env, "PWD");
	user = env_read(env, "USER");
	g_pwd = env_read(env, "PWD");
	g_usr = env_read(env, "USER");
	write(STDOUT_FILENO, "<", 1);
	if (user)
		write(STDOUT_FILENO, user, ft_strlen(user));
	write(STDOUT_FILENO, ":", 1);
	if (pwd)
		prompt_display_path(env, pwd);
	write(STDOUT_FILENO, "$> ", 3);
	if (user)
		free(user);
	if (pwd)
		free(pwd);
}

size_t			get_shell_cmd(char **env, char *line, size_t line_s)
{
	char	c_buf;
	size_t	i;

	i = 0;
	(void)env;
	ft_bzero(line, ARG_MAX);
	while (i < line_s && i < ARG_MAX)
	{
		if (read(STDIN_FILENO, &c_buf, sizeof(c_buf)) >= 0)
		{
			if (c_buf == '\n')
			{
				line[i] = '\0';
				break ;
			}
			line[i] = c_buf;
			++i;
		}
	}
	i = path_trim(line, i);
	return (i);
}
