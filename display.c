#include "ft_select.h"

static void	print_selected(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar); // Debut mode standout
	ft_putstr_fd("\033[1;32m", 2);
	ft_putendl_fd(lst->name, 2);
	ft_putstr_fd("\033[00m", 2);
	tputs(tgetstr("se", NULL), 1, ft_poutchar); // Fin mode standout
}

static void	print_current(t_lst *lst)
{
	tputs(tgetstr("so", NULL), 1, ft_poutchar); // Debut mode standout
	ft_putstr_fd("\033[1;33m", 2);
	ft_putendl_fd(lst->name, 2);
	ft_putstr_fd("\033[00m", 2);
	tputs(tgetstr("se", NULL), 1, ft_poutchar); // Fin mode standout
}

static void	choose_display(t_lst *lst)
{
	if (lst->pos)
		print_current(lst);
	else if (lst->selected)
		print_selected(lst);
	else
		ft_putendl_fd(lst->name, 2);
}

void		display_list(t_term *term)
{
	t_lst *tmp;

	tmp = term->lst;
	tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Clear
	while (tmp)
	{
		choose_display(tmp);
		tmp = tmp->next;
	}
}
