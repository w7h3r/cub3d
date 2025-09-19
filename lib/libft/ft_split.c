/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:08:56 by muokcan           #+#    #+#             */
/*   Updated: 2024/10/25 16:08:56 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_alloc(char **s)
{
	unsigned int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

static unsigned int	word_len(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static unsigned int	word_counter(char const *s, char c)
{
	unsigned int	is_word;
	unsigned int	word_count;

	word_count = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c && is_word == 0)
		{
			is_word = 1;
			word_count++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (word_count);
}

static char	*get_word(char const **s, char c)
{
	unsigned int	len;
	char			*word;

	while (**s && **s == c)
		(*s)++;
	len = word_len(*s, c);
	word = ft_substr(*s, 0, len);
	*s += len;
	return (word);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	words;
	char			**res;

	if (!s)
		return (NULL);
	words = word_counter((char *)s, c);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (*s && i < words)
	{
		res[i] = get_word(&s, c);
		if (!res[i])
		{
			free_alloc(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
