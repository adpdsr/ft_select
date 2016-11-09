/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_arrows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 18:15:15 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/09 14:15:56 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	down_arrow(t_term *term)
{
	t_lst *tmp;

	tmp = list_position(&term->lst);
	tmp->pos = 0;
	if (tmp->next)
		tmp->next->pos = 1;
	else
		term->lst->pos = 1;
}

void	up_arrow(t_term *term)
{
	t_lst *tmp;

	tmp = list_position(&term->lst);
	tmp->pos = 0;
	if (tmp->prev)
		tmp->prev->pos = 1;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->pos = 1;
	}
}

void	left_arrow(t_term *term)
{
	int		len;
	t_lst	*tmp;

	len = term->win.ws_row - 1;
	tmp = list_position(&term->lst);
	tmp->pos = 0;
	if (!tmp->prev)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->pos = 1;
		return ;
	}
	while (len > 0)
	{
		if (!tmp->prev)
			break ;
		tmp = tmp->prev;
		len--;
	}
	if (tmp)
		tmp->pos = 1;
}

void	right_arrow(t_term *term)
{
	int		i;
	int		len;
	t_lst	*tmp;

	i = 0;
	len = term->win.ws_row - 1;
	tmp = list_position(&term->lst);
	tmp->pos = 0;
	if (!tmp->next)
	{
		tmp = term->lst;
		tmp->pos = 1;
		return ;
	}
	while (i < len)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		i++;
	}
	if (tmp)
		tmp->pos = 1;
}
