/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:56:15 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 16:16:12 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "./pipex.h"

char **path_finder (char **env)
{
    char    *line;
	char	**path;
	int		i;

    line = NULL;
	i  = 0;
    while (env[i] && line == NULL)
    {
        line = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		i++;
    }
	path  = ft_split(&line[5], ':');
    return (path);
}

void check_access (int argc, char	*argv[], t_str *init)
{
	if (access(argv[1], F_OK) == -1)
		ft_error("first file doesn't exist\n");
	else if(access(argv[1], R_OK) == -1)
		ft_error("Cannot read from file 1\n");
	else
		init->fd[0] = open(argv[1], O_RDONLY);

	if (access(argv[argc - 1], F_OK) == -1)
	{
		init->fd[1] = open(argv[argc-1], O_WRONLY | O_CREAT, 0644);
		if (init->fd[1] < 0)
			ft_error("File2 doesn't exist and cannot create file 2\n");
	}
	else
	{
		init->fd[1] = open(argv[argc - 1], O_TRUNC | O_WRONLY);
		if (access(argv[argc - 1], W_OK) == -1)
			ft_error("Cannot write on file 2\n");
	}
	printf("FD INPUT %d, FD OUTPUT %d\n\n",init->fd[0], init->fd[1]);
}
