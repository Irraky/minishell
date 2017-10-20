/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:17:21 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 16:10:14 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		compile_path(char *fp, char *env_path,
		char *bin_path, char *bin)
{
	char *part1;
	char *part2;

	if (ft_strlen(bin_path) > 0)
		part1 = path_join(bin_path, bin);
	else
		part1 = ft_strdup(bin);
	if (ft_strlen(env_path) > 0)
		part2 = path_join(env_path, part1);
	else
		part2 = ft_strdup(part1);
	path_subcpy(part2, fp, 0, ft_strlen(part2));
	free(part1);
	free(part2);
	return (0);
}

int				resolve_relative_path(char **env, char *bin_path)
{
	char correct_path[PATH_MAX];
	char *home;

	path_subcpy(bin_path, correct_path, 0, ft_strlen(bin_path));
	if (ft_strlen(bin_path) > 1 &&
			bin_path[0] == '.' && bin_path[1] == '/')
		path_subcpy(bin_path + 2, correct_path,
				0, ft_strlen(bin_path) - 2);
	if (!(home = env_read(env, "HOME")))
		return (-1);
	if (bin_path[0] == '~')
	{
		path_subcpy(home, correct_path, 0, ft_strlen(home));
		path_subcpy(bin_path + 1, correct_path + ft_strlen(home),
				0, ft_strlen(bin_path) - 1);
	}
	path_subcpy(correct_path, bin_path, 0, ft_strlen(correct_path));
	free(home);
	return (0);
}

int				status_error(int signal)
{
	if (WIFEXITED(signal) == 0)
	{
		if (signal == 3)
			write(STDERR_FILENO, "Quit\n", 5);
		if (signal == 11)
			write(STDERR_FILENO, "Segfault error.\n", 16);
		else if (signal == 10)
			write(STDERR_FILENO, "Bus error.\n", 10);
	}
	return (signal);
}

int				exec_cmd(char **env, t_command *command)
{
	char	final_path[PATH_MAX];
	pid_t	pid;
	int		status;
	int		bin_err;

	resolve_relative_path(env, command->bin_path);
	compile_path(final_path, command->env_path, command->bin_path,
			command->bin_name);
	if ((bin_err = bin_exists(final_path)) < 0)
	{
		write(STDOUT_FILENO, command->bin_name, ft_strlen(command->bin_name));
		write(STDOUT_FILENO, " : ", 3);
		bin_error(bin_err);
		return (0);
	}
	pid = fork();
	if (pid == 0)
		exit(execve(final_path, command->argv, env));
	else
	{
		waitpid(pid, &status, 0);
		return (status_error(status));
	}
	return (0);
}
