/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 12:30:11 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/19 12:48:33 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	print_selected(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar);
	ft_putstr_fd(CYAN, 0);
	ft_putendl_fd(lst->name, 0);
	ft_putstr_fd(RESET, 0);
	tputs(tgetstr("se", NULL), 1, ft_poutchar);
}

static void	print_current(t_lst *lst)
{
	tputs(tgetstr("us", NULL), 1, ft_poutchar);
	ft_putstr_fd(CYAN, 0);
	ft_putendl_fd(lst->name, 0);
	ft_putstr_fd(RESET, 0);
	tputs(tgetstr("ue", NULL), 1, ft_poutchar);
}

static void	print_current_selected(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar);
	tputs(tgetstr("us", NULL), 1, ft_poutchar);
	ft_putstr_fd(CYAN, 0);
	ft_putendl_fd(lst->name, 0);
	ft_putstr_fd(RESET, 0);
	tputs(tgetstr("se", NULL), 1, ft_poutchar);
	tputs(tgetstr("ue", NULL), 1, ft_poutchar);
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
		ft_putendl_fd(lst->name, 0);
}

void		display_list(t_term *term)
{
	int		i;
	int		pos_col;
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
