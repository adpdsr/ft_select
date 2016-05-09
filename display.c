/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 12:30:11 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/09 17:27:00 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	print_selected(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar); // Debut mode standout
	ft_putstr_fd(CYAN, 2);
	ft_putendl_fd(lst->name, 2);
	ft_putstr_fd(RESET, 2);
	tputs(tgetstr("se", NULL), 1, ft_poutchar); // Fin mode standout
}

static void	print_current(t_lst *lst)
{
	tputs(tgetstr("us", NULL), 1, ft_poutchar); // Debut de soulignement
	ft_putstr_fd(CYAN, 2);
	ft_putendl_fd(lst->name, 2);
	ft_putstr_fd(RESET, 2);
	tputs(tgetstr("ue", NULL), 1, ft_poutchar); // Fin de soulignement
}

static void	print_current_selected(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar); // Debut mode standout
	tputs(tgetstr("us", NULL), 1, ft_poutchar); // Debut de soulignement
	ft_putstr_fd(CYAN, 2);
	ft_putendl_fd(lst->name, 2);
	ft_putstr_fd(RESET, 2);
	tputs(tgetstr("se", NULL), 1, ft_poutchar); // Fin mode standout
	tputs(tgetstr("ue", NULL), 1, ft_poutchar); // Fin de soulignement
}

static void	choose_display(t_lst *lst)
{
	if (lst->pos)
	{
		if (lst->selected == 1)
			print_current_selected(lst);
		else
			print_current(lst);
	}
	else if (lst->selected)
		print_selected(lst);
	else
		ft_putendl_fd(lst->name, 2);
}

void		display_list(t_term *term)
{
	int		i;
	int		ref;
	t_lst	*tmp;

	i = 1;
	ref = 0;
	tmp = term->lst;
	while (tmp)
	{
		set_display(term, ref, i);
		choose_display(tmp);
		tmp = tmp->next;
		i++;
	}
}
