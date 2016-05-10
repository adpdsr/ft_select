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
	exit_term(term);
	exit(0);
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
		if (!(tmp->next))
			escape(term);
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

void	ret_to_shell(t_term *term)
{
	char	*ret;
	t_lst	*lst;

	lst = term->lst;
	ret = NULL;
	ret = (char *)malloc(sizeof(char));
	while (lst)
	{
		if (lst->selected == 1)
		{
			ret = ft_strjoin(ret, lst->name);
			ret = ft_strjoin(ret, " ");
		}
		lst = lst->next;
	}
	exit_term(term);
	if (ft_strlen(ret))
		ft_putendl_fd(ft_strsub(ret, 0, ft_strlen(ret) - 1), 1);
	exit(0);
}
