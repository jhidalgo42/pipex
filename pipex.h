/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 18:03:38 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 16:38:55 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft/libft.h"
# include "./gnl/get_next_line.h"
# include "./ft_printf/include/ft_printf.h"

typedef struct s_str
{
    char    **path_cmd;
    char    **path_split;
    int    cmds;
    int     fd[2];
    int     i;
    int     pipes;
}       t_str;


# define READ_END	0   
# define WRITE_END	1
# define POS_FIRST_CMD 2
# define MAX_FD_VALUE 4096
# define ERR_INFILE	"Error: Infile\n"
# define ERR_OUTFILE	"Error: Outfile\n"
# define ERR_INPUT	"Error: Not right number of arguments\n"
# define ERR_PIPE	"Error: Pipe"
# define ERR_CMD	"Error: Command not found\n"6
# define EINVAL	22 /* Invalid argument */
# define EACCES	13	/* Permission denied */
# define ENODEV	19	/* Operation not supported by device */


void ft_error(char*	error);
char **path_finder (char **env);
void check_access (int argc, char	*argv[], t_str *init);

/* File descriptor control */

int	open_file_one(char **argv, int *fd_in);
void	open_pipe(t_str *init, int fd[2]);
void	close_fd(t_str *init, int fd[init->pipes][2], int fd_in[2]);

void	pipex(t_str *init, char **argv);
void	find_command_path(char *com, t_str *init);
void    command_mock(t_str *init);
void	ft_child(t_str *init, int fd[init->pipes][2]);

void	ft_error_free(t_str *all);
void	free_array(char **str);
void	join_cmd(t_str *all, char *com, char *path, int go);

void	first_command(t_str *init, int fd[init->pipes][2]);
void	last_command(t_str *init, int fd[init->pipes][2]);
void	command_process(t_str *init, int fd[init->pipes][2]);
#endif