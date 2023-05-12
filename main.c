/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 17:58:01 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 16:54:51 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "./pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	t_str	init;

	if (argc < 5)
	{
		ft_error(ERR_INPUT);
		exit(1);
	}
	init.cmds = argc - 2;
	check_access(argc, argv, &init);
	init.path_split = path_finder(env);
	init.pipes = init.cmds -1;
	printf("\n\n%d -- %d \n\n", init.fd[0], init.fd[1]);
	pipex(&init,argv);
	return (0);
}
