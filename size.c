/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:21:18 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/12 17:44:34 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void		list_size(t_term *term)
{
	int len;
	int nb_elem;
	int max_len;	
	t_lst	*tmp;

//	ft_putendl("test3.4.1");
//	sleep(1);
	nb_elem = 0;
	max_len = 0;
	tmp = term->lst;
//	ft_putendl("test3.4.2");
//	sleep(1);
	while (tmp)
	{
//		ft_putendl("test3.4.2.1");
		len = ft_strlen(tmp->name);
//		ft_putendl("test3.4.2.2");
		if (len > max_len)
			max_len = len;
//		ft_putendl("test3.4.2.3");

		nb_elem++;
		tmp = tmp->next;
//		ft_putendl("test3.4.2.4");
	}
//	ft_putendl("test3.4.3");
//	sleep(1);
	term->info.nb_elem = nb_elem;	
	term->info.max_len = max_len;	
}

void	get_size_info(t_term *term)
{
//	ft_putendl("test3.1");
//	sleep(1);
	ioctl(0, TIOCGWINSZ, &(term->win));
//	ft_putendl("test3.2");
//	sleep(1);
	term->info.nb_row = term->win.ws_row;
//	ft_putendl("test3.3");
//	sleep(1);
	term->info.nb_col = term->win.ws_col;
//	ft_putendl("test3.4");
//	sleep(1);
	list_size(term);
//	ft_putendl("test3.5");
//	sleep(1);
}

int	set_display(t_term *term, int pos_col, int i)
{
	int j;
	int nb_col;
	int nb_max;

	j = 0;
	nb_col = (term->info.nb_elem / term->win.ws_row) + 1;
	nb_max = term->info.nb_row - 2;
	if (i == 0)
		tputs(tgetstr("rc", NULL), 1, ft_poutchar); // Retour chariot	
	if (i != 0 && i % (nb_max) == 0)
	{
		pos_col += (term->info.max_len + 2);
		tputs(tgetstr("rc", NULL), 1, ft_poutchar); // Retour chariot
	}
	while (j++ <= pos_col)
		tputs(tgetstr("nd", NULL), 1, ft_poutchar); // espace
	return (pos_col);
}
