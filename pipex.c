/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 16:35:26 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 17:05:44 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"

void	pipex(t_str *init, char **argv)
{
	int	fd[MAX_FD_VALUE][2];

	init->i = 0;
    printf("R-----%d\n", init->fd[0]);
	fd[0][0] = init->fd[READ_END];
	while (init->i < init->cmds)
	{
        printf("ANTES:      i = %d R%d - W%d\n", init->i, fd[init->i][READ_END], fd[init->i][WRITE_END]);
		open_pipe(init, fd[init->i]);
        printf("DESPUES:    i = %d R%d - W%d\n\n", init->i, fd[init->i][READ_END], fd[init->i][WRITE_END]);
		find_command_path(argv[POS_FIRST_CMD + init->i], init);
        ft_child(init, fd);
		close_fd(init, fd, init->fd);
		init->i++;
		free_array(init->path_cmd);
	}
	wait(0);
	free_array(init->path_split);
}

void	find_command_path(char *com, t_str *init)
{
	char	*path;
	char	*command;
	int		go;

	go = 0;
	init->path_cmd = ft_split(com, 32);
	command = ft_strdup(init->path_cmd[0]);
	path = NULL;
	while (access(init->path_cmd[0], F_OK) == -1 && init->path_split[go])
	{
		join_cmd(init, command, path, go);
		go++;
	}
	free(command);
}


void	ft_child(t_str *init, int fd[init->pipes][2])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (init->i == 0)
			first_command(init, fd);
		if (init->i == (init->cmds - 1))
			last_command(init, fd);
		if (init->i != 0 && init->i != (init->cmds - 1))
			command_process(init, fd);
		//command_mock(init);
		exit(0);
		if (execve(init->path_cmd[0], init->path_cmd, NULL) == -1)
		{
			if (init->path_cmd)
				free_array(init->path_cmd);
			if (init->path_split)
				free_array(init->path_split);
			ft_printf("%s\n", strerror(ENODEV));
			exit(1);
		}
	}
}

// void command_mock(t_str *init)
// {
// 	if (init->i == 0) {
// 		dprintf(STDERR_FILENO, "holi from start\n");
// 		int fd_ret = write(STDOUT_FILENO, "patata palabra palabra", strlen("patata palabra palabra"));
// 		if (fd_ret == -1) {
// 			perror("first_command");
// 		}
// 	}
// 	else if (init->i == init->cmds - 1) {
// 		dprintf(STDERR_FILENO, "holi from end\n");
// 		char buffer[1001] = {0};
// 		int fd_ret = read(STDIN_FILENO, buffer, 1000);
// 		if (fd_ret == -1) {
// 			perror("last_command");
// 		}
// 		int fd_ret_2 = write(STDOUT_FILENO, buffer, strlen(buffer));
// 		if (fd_ret_2 == -1) {
// 			perror("last_command_write");
// 		}
// 	}
// 	else {
// 		dprintf(STDERR_FILENO, "holi from middle\n");
// 		char buffer[1001] = {0};
// 		int fd_ret = read(STDIN_FILENO, buffer, 1000);
// 		if (fd_ret == -1) {
// 			perror("middle_command");
// 		}
// 		int fd_ret_2 = write(STDOUT_FILENO, buffer, strlen(buffer));
// 		if (fd_ret_2 == -1) {
// 			perror("middle_command");
// 		}
// 	}
// }

