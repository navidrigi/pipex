/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:56:51 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/25 12:11:05 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_only(char *str)
{
	write (2, "pipex: ", 7);
	write (2, str, ft_strlen(str));
	write (2, ": command not found\n", 20);
	exit(EXIT_FAILURE);
}

void	exit_and_cleanup(t_data *data, char *str)
{
	free(data);
	perror(str);
	exit(EXIT_FAILURE);
}

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		s1_len;
	int		i;

	s1_len = 0;
	while (s1[s1_len])
		s1_len++;
	dest = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	my_perror(char *str)
{
	write (2, "pipex: ", 7);
	write (2, str, ft_strlen(str));
	write (2, ": ", 2);
	perror("");
}
