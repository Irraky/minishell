/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:14:21 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 16:26:50 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		shell_lvl(char **env)
{
	char	*i;
	int		lvl;

	lvl = 0;
	i = env_read(env, "SHLVL");
	if (i)
	{
		lvl = ft_atoi(i);
		lvl += 1;
		free(i);
		i = ft_itoa(lvl);
		env_write(env, "SHLVL", i);
		free(i);
	}
	else
		env_write(env, "SHLVL", "1");
}

static int		built_exit(t_command *command, char **env)
{
	int		ret;

	env_free(env);
	if (command->argv[1])
		ret = ft_atoi(command->argv[1]);
	else
		ret = 0;
	write(STDOUT_FILENO, "Bye !\n", 6);
	command_free_content(command);
	if (g_usr)
		free(g_usr);
	if (g_pwd)
		free(g_pwd);
	return (ret);
}

t_command		undermain(size_t cmd_size, char ***env, int builtin_ret)
{
	t_command	command;
	char		cmd_line[ARG_MAX];

	while (1)
	{
		command_init(&command);
		cmd_size = get_shell_cmd(*env, cmd_line, sizeof(cmd_line));
		if (cmd_size == 0)
			display_prompt(*env);
		if (cmd_size == 0)
			continue ;
		parse_shell_cmd(cmd_line, cmd_size, &command);
		path_eval(command.bin_path);
		get_env_path(*env, &command);
		*env = check_builtin(*env, &command, &builtin_ret);
		if (builtin_ret == 1)
			if (exec_cmd(*env, &command) != 2)
				display_prompt(*env);
		if (builtin_ret != 1 && builtin_ret != BUILTIN_EXIT)
			display_prompt(*env);
		if (builtin_ret == BUILTIN_EXIT)
			break ;
		command_free_content(&command);
	}
	return (command);
}

int				main(void)
{
	size_t		cmd_size;
	t_command	command;
	char		**env;
	int			builtin_ret;

	get_signal();
	env = env_dup(NULL);
	shell_lvl(env);
	display_prompt(env);
	cmd_size = 0;
	builtin_ret = 0;
	command = undermain(cmd_size, &env, builtin_ret);
	return (built_exit(&command, env));
}
