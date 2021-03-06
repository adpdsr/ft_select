/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 13:42:37 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/09 14:17:09 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_term	*ft_stock(t_term *term, int i)
{
	static t_term *tmp = NULL;

	if (i == 0)
		tmp = term;
	return (tmp);
}

t_lst	*list_position(t_lst **head)
{
	t_lst *tmp;

	if (!(*head))
		error_exit("list empty");
	tmp = *head;
	while (tmp->pos != 1)
		tmp = tmp->next;
	return (tmp);
}

int		ft_poutchar(int c)
{
	return (write(2, &c, 1));
}

void	error_exit(char *func)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(func, 2);
	exit(1);
}
