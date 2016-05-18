/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_rest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 18:15:25 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 18:48:38 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	select_cur(t_term *term)
{
		t_lst *tmp;

		tmp = list_position(&term->lst);
		if (!tmp->selected)
			tmp->selected = 1;
		else
			tmp->selected = 0;
		down_arrow(term);
}

void	escape(t_term *term)
{
		exit_term(term);
		free_list(term);
		exit(0);
}

void	del(t_term *term, t_lst **head)
{
		t_lst *tmp;

		tmp = list_position(&term->lst);
		tmp->pos = 0;
		if (*head == tmp)
		{
			if (!(tmp->next))
				escape(term);
			*head = tmp->next;
			tmp->next = *head;
			tmp->next->pos = 1;
		}
		if (tmp->next)
		{
			tmp->next->pos = 1;
			tmp->next->prev = tmp->prev;
		}
		if (tmp->prev)
		{
			if (!(tmp->next))
				tmp->prev->pos = 1;
			tmp->prev->next = tmp->next;
		}
		free(tmp);
}

static int more_res(t_lst *lst)
{
		t_lst *tmp;

		tmp = lst;
		while (tmp)
		{
			if (tmp->selected == 1)
				return (1);
			tmp = tmp->next;
		}
		return (0);
}

void	ret_to_shell(t_term *term)
{
		int		i;
		int		first;
		t_lst	*lst;

		i = 0;
		lst = term->lst;
		exit_term(term);
		while (lst)
		{
			first = 0;
			if (lst->selected == 1)
			{
				ft_putstr_fd(lst->name, 1);
				first = 1;
			}
			if (lst->next)
				if (more_res(lst->next) && first)
					ft_putchar_fd(' ', 1);
			lst = lst->next;
		}
		free_list(term);
		exit(0);
}
