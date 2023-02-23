/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:20:33 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/23 10:16:24 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
int	words_conts(char *s, char *list, char c)
{
	size_t	i;
	int		size;
	char	*f;

	i = 0;
	size = 0;
	while (s[i])
	{
		f = ft_strchr(list, s[i]);
		printf("%s\n", f);
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			size++;
		while (s && s[i] && s[i] != c)
		{
			if (s[i] == list[0])
			{
				i++;
				while (s[i] && s[i] != list[0])
				{
					printf("%c", s[i]);
					i++;
				}
			}
			i++;
		}
	}
	return (size);
}
*/

/*
int	words_conts(char *s, char *list, char c)
{
	size_t	i;
	int		size;
	char	*f;

	i = 0;
	size = 0;
	while (s[i])
	{
		f = ft_strchr(list, s[i]);
		printf("%s\n", f);
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			size++;
		while ((s && s[i] && s[i] != c) || (f && *f && s && s[i]))
			i++;
	}
	return (size);
}
*/

char	**ft_str_split(char *s, char *list, char c)
{
	(void)s;
	(void)list;
	(void)c;
	return (NULL);
}
