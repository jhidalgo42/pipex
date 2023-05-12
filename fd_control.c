/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_control.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:02:35 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 17:02:19 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file_one(char **argv, int *fd_in)
{
    close (*fd_in);
    *fd_in = open(argv[1], O_RDWR);
	return (*fd_in);
}

void	open_pipe(t_str *init, int fd[2])
{
	if (init->i < (init->cmds))
	{
		if (pipe(fd) == -1)
			ft_error_free(init);			
    }
}

void	close_fd(t_str *init, int fd[init->pipes][2], int fd_in[2])
{
	if (init->i == 0)
	{
		close(fd[init->i][WRITE_END]);
		close(fd_in[READ_END]);
	}
	if (init->i == (init->cmds - 1))
	{
		close(fd[init->i - 1][READ_END]);
		close(fd_in[WRITE_END]);
	}
	if (init->i != 0 && init->i != (init->cmds - 1))
	{
		close(fd[init->i - 1][READ_END]);
		close(fd[init->i][WRITE_END]);
	}
}
