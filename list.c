/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 12:11:08 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/09 17:27:02 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	list_push_back(t_lst **head, t_lst *new)
{
	t_lst	*cur;

	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
}

static t_lst	*list_create_node(char *av, int i)
{
	t_lst	*new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->name = ft_strdup(av);
	new->len = ft_strlen(av);
	new->id = i;
	i == 1 ? (new->pos = 1) : (new->pos = 0);
	new->selected = 0;
	new->next = NULL;
	new->prev = NULL;
	i = 0;
	return (new);
}

void		init_list(t_term *term, char **av)
{
	int	i;

	i = 0;
	term->lst = NULL;
	while (av[++i])
		list_push_back(&term->lst, list_create_node(av[i], i));
}
