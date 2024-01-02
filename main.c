/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:28:07 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/25 11:44:06 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc != 5)
		exit_only("Invalid number of arguments");
	data = init_data(argv, envp);
	if (pipe(data->pipefd) == -1)
		exit_only("pipe");
	data->pid1 = fork();
	if (data->pid1 == -1)
		exit_only("fork 1");
	if (data->pid1 == 0)
		child_1(data);
	else
		parent(data);
}

t_data	*init_data(char **argv, char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit_only("Malloc error");
	data->cmd1 = extract_cmd_name(argv[2]);
	if (!data->cmd1)
		exit_only("command not found");
	data->cmd2 = extract_cmd_name(argv[3]);
	if (!data->cmd2)
	{
		free(data->cmd1);
		free(data);
		exit_only("command not found");
	}
	data->args1 = ft_split(argv[2]);
	data->args2 = ft_split(argv[3]);
	data->fd1 = open(argv[1], O_RDONLY);
	if (data->fd1 == -1)
		my_perror(argv[1]);
	data->fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd2 == -1)
		perror(argv[4]);
	data->envp = envp;
	return (data);
}

void	child_1(t_data *data)
{
	data->cmd1_path = find_cmd_path(data, data->cmd1);
	if (data->cmd1_path == NULL)
		command_not_found(data, data->cmd1);
	else if (data->fd1 != -1 && data->args1)
	{
		if (close(data->pipefd[0]) == -1)
			exit_only("close pipefd[0]");
		if (dup2(data->fd1, STDIN_FILENO) == -1)
			exit_only("dup2 fd1");
		if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
			exit_only("dup2 pipefd[1]");
		if (close(data->pipefd[1]) == -1)
			exit_only("close pipefd[1]");
		if (execve(data->cmd1_path, data->args1, data->envp) == -1)
			exit_only("execve 1");
	}
}

void	child_2(t_data *data)
{
	data->cmd2_path = find_cmd_path(data, data->cmd2);
	if (data->cmd2_path == NULL)
		command_not_found(data, data->cmd2);
	else if (data->args2)
	{
		if (close(data->pipefd[1]) == -1)
			exit_only("close pipefd[1]");
		if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
			exit_only("dup2 in child2");
		if (dup2(data->fd2, STDOUT_FILENO) == -1)
			exit_only("dup2 in child2");
		if (close(data->pipefd[0]) == -1)
			exit_only("close pipefd[0]");
		if (execve(data->cmd2_path, data->args2, data->envp) == -1)
			exit_only("execve 2");
	}
}

void	parent(t_data *data)
{
	data->pid2 = fork();
	if (data->pid2 == -1)
		exit_only("fork 2");
	else if (data->pid2 == 0)
		child_2(data);
	cleanup(data);
}
