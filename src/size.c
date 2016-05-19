/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:21:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/19 12:53:38 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	list_size(t_term *term)
{
	int		len;
	int		nb_elem;
	int		max_len;
	t_lst	*tmp;

	nb_elem = 0;
	max_len = 0;
	tmp = term->lst;
	while (tmp)
	{
		len = ft_strlen(tmp->name);
		if (len > max_len)
			max_len = len;
		nb_elem++;
		tmp = tmp->next;
	}
	term->info.nb_elem = nb_elem;
	term->info.max_len = max_len;
}

void		get_size_info(t_term *term)
{
	ioctl(0, TIOCGWINSZ, &(term->win));
	term->info.nb_row = term->win.ws_row;
	term->info.nb_col = term->win.ws_col;
	list_size(term);
}

int			check_size(t_term *term)
{
	int nb_col;

	if (term->info.nb_row == 1)
	{
		tputs(tgetstr("cl", NULL), 1, ft_poutchar);
		ft_putendl_fd("window size too small", 2);
		return (1);
	}
	nb_col = (term->info.nb_elem / (term->info.nb_row - 1));
	if (nb_col == 0)
		nb_col = 1;
	if (((term->info.nb_row - 1) * nb_col) < term->info.nb_elem)
		nb_col++;
	if (((term->info.max_len + 2) * nb_col) > term->info.nb_col)
	{
		tputs(tgetstr("rc", NULL), 1, ft_poutchar);
		tputs(tgetstr("cd", NULL), 1, ft_poutchar);
		ft_putendl_fd("window size too small", 2);
		return (1);
	}
	return (0);
}

int			set_display(t_term *term, int pos_col, int i)
{
	int j;
	int nb_col;
	int nb_max;

	j = 0;
	nb_col = (term->info.nb_elem / (term->info.nb_row - 1));
	if (nb_col == 0)
		nb_col = 1;
	if (((term->info.nb_row - 1) * nb_col) < term->info.nb_elem)
		nb_col++;
	nb_max = term->info.nb_row - 1;
	if (i != 0 && i % (nb_max) == 0)
	{
		pos_col += (term->info.max_len + 2);
		tputs(tgetstr("rc", NULL), 1, ft_poutchar);
	}
	while (j++ <= pos_col)
		tputs(tgetstr("nd", NULL), 1, ft_poutchar);
	return (pos_col);
}
