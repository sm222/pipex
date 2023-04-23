/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_ft.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anboisve <anboisve@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:40:23 by anboisve          #+#    #+#             */
/*   Updated: 2023/04/23 11:02:24 by anboisve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
look at the size of the linked list
*/
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

/*
create one node of t_pid
*/
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

/*
free all the node from the linked list
*/
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

/*
take the address of the linked list and add a node at the end
if it fails return 0 else return 1
*/
int	make_pid_node(t_pids **head, pid_t pid)
{
	t_pids	*tmp;

	tmp = NULL;
	if (!(*head))
	{
		(*head) = make_node(pid);
		if (!(*head))
		{
			free_pid(head);
			return (0);
		}
		else
			return (1);
	}
	tmp = (*head);
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_node(pid);
	if (!tmp->next)
	{
		free_pid(head);
		return (0);
	}
	return (1);
}

/*
loop on all the linked list and wait on the pid.
after it free it and go to the next one
*/
void	wait_node(t_pids **head)
{
	t_pids	*tmp;
	t_pids	*next;

	tmp = (*head);
	while (tmp)
	{
		waitpid(tmp->pid, NULL, 0);
		next = tmp->next;
		ft_safe_free(tmp);
		tmp = next;
	}
}
