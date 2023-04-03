/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 10:20:33 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/03 17:42:04 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	give_index(char **list, char in)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		if (in == list[i][0] && ft_strlen(list[i]) > 1)
			return (list[i][1]);
		i++;
	}
	return (0);
}

int	catch_type(const char c, char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		if (list[i][0] == c)
			return (ft_strlen(list[i]));
		i++;
	}
	return (0);
}

static char	**return_double(t_list *lst)
{
	char	**tmp;
	t_list	*keep;
	t_list	*next_node;
	size_t	i;

	i = 0;
	tmp = ft_calloc(ft_lstsize(lst) + 1, sizeof(char *));
	keep = lst;
	while (keep)
	{
		tmp[i++] = keep->content;
		next_node = keep->next;
		free(keep);
		keep = next_node;
	}
	tmp[i] = NULL;
	return (tmp);
}

char	*ft_strdup_filter(const char *str, char *filter)
{
	size_t	i;
	char	*new;

	i = 0;
	while (str[i] && ft_strchr(filter, str[i]) == NULL)
		i++;
	new = ft_calloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (i--)
		new[i] = str[i];
	return (new);
}

char	**ft_str_split(const char *s, char **list)
{
	t_list	*data;
	size_t	i;
	size_t	j;
	char	*tmp;
	char	mem;

	data = NULL;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (catch_type(s[i], list) == 1)
			i++;
		if (catch_type(s[i + j], list) == 2)
		{
			mem = give_index(list, s[i + j++]);
			while (s[i + j] != mem)
				j++;
			j++;
		}
		else
		{
			while (catch_type(s[i + j], list) == 0)
				j++;
		}
		tmp = ft_substr(s, i, j);
		ft_lstadd_back(&data, ft_lstnew(tmp));
		if (ft_strlen(tmp))
			i += ft_strlen(tmp);
		else
			i++;
	}
	return (return_double(data));
}
