/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhidalgo <jhidalgo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:15:20 by jhidalgo          #+#    #+#             */
/*   Updated: 2023/04/25 16:13:42 by jhidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex.h"


void	ft_error_free(t_str *init)
{
	if (init->path_cmd)
		free_array(init->path_cmd);
	if (init->path_split)
		free_array(init->path_split);
	perror("Error");
	exit(1);
}

void	free_array(char **str)
{
	int	count;

	count = 0;
	if (str)
	{
		while (str[count])
		{
			free(str[count]);
			count++;
		}
	}
	free(str);
}

void	join_cmd(t_str *init, char *com, char *path, int go)
{
	free(init->path_cmd[0]);
	path = ft_strjoin(init->path_split[go], "/");
	if (!path)
		free(path);
	init->path_cmd[0] = ft_strjoin(path, com);
	free(path);
}
