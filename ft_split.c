/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narigi-e <narigi-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:17:57 by narigi-e          #+#    #+#             */
/*   Updated: 2023/10/20 16:17:57 by narigi-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_words(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_space(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			quote = str[i];
			i++;
			little_calcs(str, &i, quote);
			if (str[i] == '\0')
				break ;
		}
		while (str[i] && !is_space(str[i]))
			i++;
	}
	return (count);
}

void	little_calcs(char *str, int *i, char quote)
{
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

char	*get_word(char *str, int *i)
{
	char	*word;
	int		j;
	char	quote;

	word = malloc(sizeof(char) * 1024);
	if (!word)
		return (NULL);
	j = 0;
	while (is_space(str[*i]))
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		quote = str[(*i)++];
		while (str[*i] && str[*i] != quote)
			word[j++] = str[(*i)++];
		if (str[*i] == quote)
			(*i)++;
	}
	else
	{
		while (str[*i] && !is_space(str[*i]))
			word[j++] = str[(*i)++];
	}
	word[j] = '\0';
	return (word);
}

char	**ft_split(char *str)
{
	char	**words;
	int		i;
	int		j;
	int		count;

	count = count_words(str);
	words = malloc(sizeof(char *) * (count + 1));
	if (!words)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count)
	{
		words[j] = get_word(str, &i);
		if (!words[j])
			return (NULL);
		j++;
	}
	words[j] = NULL;
	return (words);
}
