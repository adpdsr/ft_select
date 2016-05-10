/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:21:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/10 17:31:59 by adu-pelo         ###   ########.fr       */
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

int	set_display(t_term *term, t_lst *lst, int id_col, int i, int max)
{
	int j;
	int nb_col;
	int	nb_elem_par_col;

	update_size(term);

	nb_col = term->siz.nb_elem / term->win.ws_row;
	nb_elem_par_col = term->win.ws_row;

	if (i % term->win.ws_row == 0)
	{
		tputs(tgetstr("rc", NULL), 1, ft_poutchar); // Retour chariot
		max *= 2;
		id_col++;
	}
	j = 0;
	if (id_col != 0)
	{
		term->siz.max_len *= 2;
		while (j < max)
		{
			tputs(tgetstr("nd", NULL), 1, ft_poutchar);	// espace
			j++;
		}
	}
	return (max);
}
