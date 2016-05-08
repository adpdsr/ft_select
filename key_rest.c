#include "ft_select.h"

void            select_cur(t_term *term)
{
	t_lst *tmp;

	tmp = list_position(&term->lst);
	if (!tmp->selected)
		tmp->selected = 1;
	else
		tmp->selected = 0;
	down_arrow(term);
}

void            escape(t_term *term)
{
	exit(1);
}

void            del(t_term *term, t_lst **head)
{
	t_lst *tmp;

	tmp = list_position(&term->lst);
	tmp->pos = 0;

	if (!(*head) || !tmp)
		error_exit("list empty");
	if (*head == tmp)
	{
		if (!(tmp->next)) // exit si plus d'element dans la liste
			exit(0);
		*head = tmp->next;
		tmp->next = *head;
		tmp->next->pos = 1;
	}
	if (tmp->next)
	{
		tmp->next->pos = 1;
		tmp->next->prev = tmp->prev;
	}
	if (tmp->prev)
	{
		if (!(tmp->next))
			tmp->prev->pos = 1;
		tmp->prev->next = tmp->next;
	}
	free(tmp);
}
