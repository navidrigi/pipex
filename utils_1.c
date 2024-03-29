/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:33:23 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/24 16:33:32 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_cmd_name(char *argv)
{
	int		i;
	char	*cmd_name;

	i = 0;
	if (!argv)
		exit_only ("");
	while (argv[i] && argv[i] != ' ')
		i++;
	cmd_name = (char *) malloc((i + 1) * sizeof(char));
	if (!cmd_name)
		return (0);
	strncpy(cmd_name, argv, i);
	cmd_name[i] = '\0';
	return (cmd_name);
}

char	*find_cmd_path(t_data *data, char *cmd)
{
	char	**paths;
	char	*right_path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr((data->envp)[i], "PATH", 4) == 0)
		i++;
	paths = ft_splitt((data->envp[i] + 5), ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		right_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(right_path, F_OK) == 0)
			return (right_path);
		free (right_path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free (paths);
	return (0);
}
