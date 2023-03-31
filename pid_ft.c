/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:40:23 by anboisve          #+#    #+#             */
/*   Updated: 2023/03/31 13:31:25 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	node_len(t_pids *head)
{
	size_t	i;

	i = 1;
	if (!head)
		return (0);
	while (head)
	{
		if (head->next)
			i++;
		head = head->next;
	}
	return (i);
}

t_pids	*make_node(pid_t pid)
{
	t_pids	*tmp;

	tmp = NULL;
	tmp = ft_calloc(1, sizeof(t_pids));
	if (!tmp)
		return (NULL);
	tmp->pid = pid;
	return (tmp);
}

void	free_pid(t_pids	**pids)
{
	t_pids	*next_node;

	if (!(*pids))
		return ;
	while ((*pids))
	{
		next_node = (*pids)->next;
		ft_safe_free((*pids));
		(*pids) = next_node;
	}
	(*pids) = NULL;
}

int	make_pid_node(t_pids **head, pid_t pid)
{
	t_pids	*tmp;

	tmp = NULL;
	if (!(*head))
	{
		(*head) = make_node(pid);
		if (!(*head))
			return (0);
		else
			return (1);
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_node(pid);
	if (!tmp->next)
		return (0);
	return (1);
}
