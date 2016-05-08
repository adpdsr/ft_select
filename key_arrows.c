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

}

void            right_arrow(t_term *term)
{

}
