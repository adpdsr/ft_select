/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:21:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/09 17:27:03 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	get_screen_size(t_term *term)
{
	ioctl(0, TIOCGWINSZ, &(term->win));
	term->siz.nb_row = term->win.ws_row;
	term->siz.nb_col = term->win.ws_col;
}

int		list_len(t_lst *lst)
{
	int len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

int		list_max_len(t_lst *lst)
{
	int len;
	int max_len;

	max_len = 0;
	while (lst)
	{
		len = ft_strlen(lst->name);
		if (len > max_len)
			max_len = len;
		lst = lst->next;
	}
	return (max_len);
}

void	update_size(t_term *term)
{
	t_size	*siz;
	t_lst	**head;
   
	head = &term->lst;
	siz = &term->siz;
	siz->nb_elem = list_len(*head);
	siz->max_len = list_max_len(*head);
	siz->nb_col = term->win.ws_col / (siz->max_len + 4);
}

void	set_display(t_term *term, int ref, int i)
{
	int j;
	int col;
	int	elem_col;

	update_size(term);
	elem_col = (list_len(term->lst) + 1) / (term->siz.nb_col - 1);

	/*
	   ft_putstr_fd("shell x : ", 2);
	   ft_putnbr_fd(siz->nb_col, 2);
	   ft_putendl_fd("", 2);

	   ft_putstr_fd("shell y : ", 2);
	   ft_putnbr_fd(siz->nb_row, 2);
	   ft_putendl_fd("", 2);

	   ft_putstr_fd("col : ", 2);
	   ft_putnbr_fd(col, 2);
	   ft_putendl_fd("", 2);

	   ft_putstr_fd("elem_col : ", 2);
	   ft_putnbr_fd(elem_col, 2);
	   ft_putendl_fd("", 2);
	   */

	if (i % (elem_col + 1) == 0)
	{
		tputs(tgetstr("rc", NULL), 1, ft_poutchar);
		ref++;
	}

	j = 0;
	if (ref)
		while (j < term->siz.max_len + 4)
		{
			tputs(tgetstr("nd", NULL), 1, ft_poutchar);	
			j++;
		}
}
