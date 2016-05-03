/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 12:11:08 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/03 16:54:37 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		list_push_back(t_lst **head, t_lst *new)
{
	t_lst *cur;

	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

static t_lst	*list_create_node(char *str)
{
	static int i = 0;
	t_lst *new;

	if (!(new = malloc(sizeof(t_lst))))
		return (NULL);
	new->name = ft_strdup(str);
	new->len = ft_strlen(str);
	new->selected = 0;
	if (i == 0)
		new->first = 1;
	else
		new->first = 0;
	new->next = NULL;
	i += 1;
	return (new);
}

void			print_list(t_lst **head) // test
{
	t_lst *tmp;

	tmp = *head;
	ft_putendl("printing list");
	while (tmp)
	{
		ft_putendl("new elem");
		ft_putstr("name: ");
		ft_putendl(tmp->name);
		ft_putstr("len: ");
		ft_putnbr(tmp->len);
		ft_putchar('\n');
		ft_putstr("selected: ");
		ft_putnbr(tmp->selected);
		ft_putchar('\n');
		ft_putstr("first: ");
		ft_putnbr(tmp->first);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void			init_list(t_lst *lst, char **av)
{
	lst = NULL;

	while (*(++av))
		list_push_back(&lst, list_create_node(*av));
	print_list(&lst); // test
}
