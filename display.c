/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 12:30:11 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 17:35:27 by adu-pelo         ###   ########.fr       */
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

static int	check_size(t_term *term)
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
		tputs(tgetstr("cl", NULL), 1, ft_poutchar);
		ft_putendl_fd("window size too small", 2);
		return (1);
	}
	return (0);
}

void		display_list(t_term *term)
{
	int	i;
	int	pos_col;
	t_lst	*tmp;

	i = 0;
	pos_col = -1;
	tmp = term->lst;
	get_size_info(term);
	if (check_size(term))
		return ;
	while (tmp)
	{
		pos_col = set_display(term, pos_col, i);
		choose_display(tmp);
		tmp = tmp->next;
		i++;
	}
}
