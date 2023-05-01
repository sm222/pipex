/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:12:06 by anboisve          #+#    #+#             */
/*   Updated: 2023/05/01 15:05:11 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
while the user put text inside the file and it not the end word it loop
*/
void	loop_in(t_pipex *data)
{
	char	*tmp;

	while (1)
	{
		ft_putstr_fd("here_doc > ", 1);
		tmp = get_next_line(0);
		if (ft_strncmp(tmp, data->argv[2], ft_strlen(data->argv[2])) == 0)
		{
			if (ft_strncmp(tmp + ft_strlen(data->argv[2]), "\n", 2) == 0)
			{
				ft_safe_free(tmp);
				break ;
			}
		}
		else if (!tmp)
			ft_exit(data, errno, "get_next_line");
		ft_putstr_fd(tmp, data->input);
		ft_safe_free(tmp);
	}
}

/*
create a file name "here_doc"
and safe the user input inside
*/
void	here_doc(t_pipex *data)
{
	data->input = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (data->input < 0)
		ft_exit(data, 1, "can't make here_doc");
	loop_in(data);
	close(data->input);
	data->input = open("/tmp/here_doc", O_RDONLY, 0644);
	if (data->input < 0)
		ft_exit(data, 1, "can't re_open here_doc");
}
