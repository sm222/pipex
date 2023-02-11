/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:09:21 by anboisve          #+#    #+#             */
/*   Updated: 2023/02/08 13:08:10 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_p(unsigned long p)
{
	char	*tmp;
	int		size;

	size = ft_putstr_fd("0x", STDOUT_FILENO);
	tmp = ft_ulltoa((unsigned long)p, 16);
	size += ft_putstr_fd(tmp, STDOUT_FILENO);
	if (tmp)
		ft_safe_free(tmp);
	return (size);
}
