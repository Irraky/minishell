/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_eval.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:14:50 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 15:40:17 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_env_path(char **env, t_command *command)
{
	size_t	i;
	char	**path_contents;
	char	*path;
	char	*test_path;

	if (!(path = env_read(env, "PATH")))
		return (0);
	path_contents = ft_strsplit(path, ':');
	i = 0;
	while (path_contents[i] != NULL)
	{
		test_path = path_join(path_contents[i], command->bin_name);
		if (bin_exists(test_path) == 0)
			path_subcpy(path_contents[i], command->env_path,
					0, ft_strlen(path_contents[i]));
		free(path_contents[i]);
		free(test_path);
		++i;
	}
	free(path_contents);
	free(path);
	return (0);
}

int			bin_exists(const char *path)
{
	struct stat		data;

	if (access(path, F_OK) != 0)
		return (-1);
	if (access(path, X_OK) != 0)
		return (-2);
	if (stat(path, &data) == -1)
		return (-1);
	if (!(S_ISREG(data.st_mode)))
		return (-1);
	return (0);
}

int			bin_error(const int error_no)
{
	if (error_no == -1)
		write(STDERR_FILENO, ERR_NOT_FOUND, sizeof(ERR_NOT_FOUND));
	if (error_no == -2)
		write(STDERR_FILENO, ERR_DENIED, sizeof(ERR_DENIED));
	return (0);
}

int			get_env_path(char **env, t_command *command)
{
	if (ft_strlen(command->bin_path) == 0)
		search_env_path(env, command);
	return (0);
}
