# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: drecours <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/10 16:14:41 by drecours          #+#    #+#              #
#    Updated: 2017/10/19 16:10:47 by drecours         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
FLAGS = -Werror -Wall -Wextra 
SRC = main.c \
	command.c \
	ft_strncmp.c \
	ft_splitspaces.c \
	ft_strsplit.c \
	ft_strdup.c \
	ft_strcmp.c \
	ft_strlen.c \
	ft_strjoin.c \
	ft_bzero.c \
	get_shell_cmd.c \
	parse_shell_cmd.c \
	path_eval.c \
	path_tools.c \
	env.c \
	env_tools.c \
	bin_eval.c \
	dir_eval.c \
	exec.c \
	builtin.c \
	builtin_env.c \
	builtin_misc.c \
	signal.c \
	ft_itoa.c \
	ft_atoi.c \
	env_protec.c \
	builtin_cd.c \
   	ft_strchr.c \
	misc.c \
	ft_42.c

OBJ = $(SRC:.c=.o)
CC = gcc

all: $(NAME)

$(NAME): $(OBJ)  
		$(CC) $(FLAGS) -o $(NAME) $(SRC)

clean:
	rm -f $(OBJ)
	
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
