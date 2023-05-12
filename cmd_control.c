/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:13:09 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/27 10:03:50 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_command(t_str *init, int fd[init->pipes][2])
{
	dprintf(STDERR_FILENO, "[ Fcommand %d ] [ %d, %d ]\n", init->i, init->fd[READ_END], fd[init->i][WRITE_END]);	
	if (dup2(init->fd[READ_END], 0) == -1)
		ft_error("PIPE FIRST COMMAND");//_free(init);
	close(init->fd[READ_END]);
	if (dup2(fd[init->i][WRITE_END], 1) == -1)
		ft_error("PIPE FIRST COMMAND");//_free(init);
	close(fd[init->i][WRITE_END]);
	close(fd[init->i][READ_END]);
	close(init->fd[WRITE_END]);
}

void	last_command(t_str *init, int fd[init->pipes][2])
{
	dprintf(STDERR_FILENO, "[ Lcommand %d ] [ %d, %d ]\n", init->i, fd[init->i -1][READ_END], init->fd[WRITE_END]);	
	if (dup2(fd[init->i - 1][READ_END], 0) == -1)
		ft_error("PIPE LAST COMMANDA");//_free(init);
	close(fd[init->i - 1][READ_END]);
	if (dup2(init->fd[WRITE_END], 1) == -1)
		ft_error("PIPE LAST COMMANDB");//_free(init);
	if (init->cmds != 2)
	{
		close(fd[init->i][READ_END]);
		close(fd[init->i][WRITE_END]);
	}
	close(init->fd[WRITE_END]);
}

void	command_process(t_str *init, int fd[init->pipes][2])
{
	dprintf(STDERR_FILENO, "[ Mcommand %d ] [ %d, %d ]\n", init->i, fd[init->i -1][READ_END], fd[init->i][WRITE_END]);
	if (dup2(fd[init->i - 1][READ_END], 0) == -1)
		ft_error("COMMAND_PROCESS");//_free(init);
	close(fd[init->i - 1][READ_END]);
	if (dup2(fd[init->i][WRITE_END], 1) == -1)
		ft_error("COMMAND PROCESS");//_free(init);
	close(fd[init->i][WRITE_END]);
	close(fd[init->i][READ_END]);
	close(init->fd[WRITE_END]);
}
