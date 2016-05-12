/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:56:28 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/12 17:44:36 by adu-pelo         ###   ########.fr       */
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

static void	resize(int signal)
{

	static t_term	*term;
	struct winsize	win;

	term = NULL;
	term = ft_stock(term, 1);
	tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Effacer ecran et mettre curseur au debut
	display_list(term);
}

void	catch_signal(void)
{
	signal(SIGWINCH, resize);
	//	signal(SIGTSTP, stop);
	//	signal(SIGCONT, restart);
	//	signal(SIGINT, end);
}
