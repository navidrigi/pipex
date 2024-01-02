/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 15:10:42 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/24 15:07:43 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

void	cleanup(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->fd1);
	close(data->fd2);
	waitpid(data->pid1, &(data->status1), 0);
	waitpid(data->pid2, &(data->status2), 0);
	if (WIFEXITED(data->status2))
		exit_code = WEXITSTATUS(data->status2);
	if (data->cmd1)
		free(data->cmd1);
	if (data->cmd2)
		free(data->cmd2);
	if (data->args1)
		free_array(data->args1);
	if (data->args2)
		free_array(data->args2);
	if (data)
		free(data);
	exit (exit_code);
}

void	free_child_1(t_data *data)
{
	if (data->cmd1)
		free(data->cmd1);
	if (data->args1)
		free_array(data->args1);
	if (data)
		free(data);
}

void	free_child_2(t_data *data)
{
	if (data->cmd2)
		free(data->cmd2);
	if (data->args2)
		free_array(data->args2);
	if (data)
		free(data);
}
