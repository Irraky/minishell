/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drecours <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 16:24:59 by drecours          #+#    #+#             */
/*   Updated: 2017/10/19 15:55:18 by drecours         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/syslimits.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>

char			*g_pwd;
char			*g_usr;

typedef struct	s_command
{
	char		bin_name[NAME_MAX];
	char		bin_path[PATH_MAX];
	char		env_path[PATH_MAX];
	int			argc;
	char		**argv;
}				t_command;

/*
** ERRORS
*/

# define ERR_NOT_FOUND "Command not found.\n"
# define ERR_DENIED "Access denied.\n"
# define CD_NOT_FOUND ": No such file or directory.\n"
# define CD_TOO_MANY "cd: Too many arguments.\n"
# define CD_NO_RIGHT ": Permission denied.\n"
# define CD_NOT_DIR ": Not a directory.\n"
# define STAT_ERROR "Problem with stat function.\n"
# define EX_SYNTAX "exit: Expression Syntax.\n"
# define CD_USAGE "Usage: cd [-|<dir>]\n"

/*
** BUILT IN SIGNALS
*/

# define BUILTIN_EXIT -10

/*
** MINISHELL TOOLS
*/

size_t			path_trim(char *path, size_t size);
size_t			path_subcpy(const char *source, char *dest, size_t start,
				size_t len);
char			*path_join(const char *path, const char *bin);
int				command_init(t_command *command);
int				command_free_content(t_command *command);
void			get_signal(void);
char			**ft_path(char *pwd, t_command *cmd, char **env);
int				fix_root(char *path);

/*
** MINISHELL FUNCTIONS
*/

size_t			get_shell_cmd(char **env, char *line, size_t line_s);
int				parse_shell_cmd(char *cmd, size_t cmd_size, t_command *command);
void			display_prompt(char **env);

char			**env_dup(char **environ);
char			**test_env(t_command *command, char **env, int *i);
int				env_free(char **env);
char			*env_key(char *env_v);
char			*env_val(char *env_v);
char			*env_read(char **env, const char *key);
char			**env_add(char **env, const char *env_val);
char			**env_write(char **env, const char *key, const char *val);
char			**builtin_42(char **env);
char			**env_protec(char **env);
char			**env_error(char **new_env, char *str);
char			**setenv_error(char **env);

int				path_eval(char *path);
int				get_env_path(char **env, t_command *command);
int				bin_exists(const char *path);
int				bin_error(const int error_no);
int				dir_exists(char *path);
int				resolve_relative_path(char **env, char *bin_path);

int				exec_cmd(char **env, t_command *command);

char			**check_builtin(char **env, t_command *command, int *exec);
char			**builtin_setenv(char **env, t_command *command);
char			**builtin_unsetenv(char **env, t_command *command);
char			**manage_env(t_command *command, char **env, int i);
char			**builtin_env(char **env, t_command *command);
char			**builtin_cd(char **env, t_command *command);
char			**cd_minus(char **env, t_command *command);
char			**cd_error(char **env, int err, char *str, t_command *command);
char			**builtin_echo(char **env, t_command *command);
char			**builtin_exit(char **env, t_command *command, int *exec);
int				status_error(int signal);

/*
** ADDITIONAL FUNCTIONS
*/

int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			**ft_splitspaces(char const *str);
char			**ft_strsplit(char const *str, char c);
char			*ft_strdup(const char *s1);
int				ft_strcmp(const char *s1, const char *s2);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_bzero(void *s, size_t n);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
char			*ft_strchr(const char *s, int c);
int				alph_num(const char *str);

#endif
