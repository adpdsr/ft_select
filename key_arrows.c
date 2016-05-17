#include "ft_select.h"

void            down_arrow(t_term *term)
{
	t_lst *tmp;

	tmp = list_position(&term->lst);
	tmp->pos = 0;
	if (tmp->next)
		tmp->next->pos = 1;
	else
		term->lst->pos = 1;
}

void            up_arrow(t_term *term)
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

void            left_arrow(t_term *term)
{
	int		len;
	t_lst	*tmp;

	len = term->win.ws_row - 1;
	tmp = list_position(&term->lst);
	tmp->pos = 0;
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

void            right_arrow(t_term *term)
{
	int		i;
	int		len;
	t_lst	*tmp;

	i = 0;
	len = term->win.ws_row - 1;
	tmp = list_position(&term->lst);
	tmp->pos = 0;
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
