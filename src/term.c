/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 11:25:28 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 18:33:45 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

void	init_term(t_term *term)
{
	if (!(term->name_term = getenv("TERM")))
		error_exit("getenv");
	if (tgetent(NULL, term->name_term) < 1)
		error_exit("tgetent");
	if (tcgetattr(0, &(term->termios)) == -1)
		error_exit("tcgetattr");
	term->termios.c_lflag &= ~(ICANON);
	term->termios.c_lflag &= ~(ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (tcsetattr(0, 0, &(term->termios)) == -1)
		error_exit("tcsetattr");
	tputs(tgetstr("vi", NULL), 1, ft_poutchar);
}

void	exit_term(t_term *term)
{
	if (tcgetattr(0, &term->termios) == -1)
		error_exit("tcgetattr");
	term->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &(term->termios)) == -1)
		error_exit("tcsetattr");
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
}
