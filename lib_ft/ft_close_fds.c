/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 11:13:41 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/31 17:32:04 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
use to close file descriptors.
open by pipe on a 2D array.
if f_prt = 1 the 2D array will be free
*/
int	ft_close_fds(int **fds, int f_ptr)
{
	int	i;
	int	close_nb;

	i = 0;
	close_nb = 0;
	while (fds && fds[i])
	{
		if (close(fds[i][0]) == 0)
			close_nb++;
		if (close(fds[i][1]) == 0)
			close_nb++;
		if (f_ptr)
		fds[i] = ft_safe_free(fds[i]);
		i++;
	}
	if (f_ptr)
		fds = ft_safe_free(fds);
	return (close_nb);
}
