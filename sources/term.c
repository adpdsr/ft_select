/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 11:25:28 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/09 14:17:00 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	init_term(t_term *term)
{
	if (!isatty(0))
		error_exit("isatty");
	if ((term->fd = open(ttyname(0), O_RDWR)) == -1)
		error_exit("tyyname");
	if (tgetent(NULL, getenv("TERM")) < 1)
		error_exit("tgetent");
	if (tcgetattr(term->fd, &(term->termios)) == -1)
		error_exit("tcgetattr");
	term->termios.c_lflag &= ~(ICANON);
	term->termios.c_lflag &= ~(ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	if (tcsetattr(term->fd, TCSANOW, &(term->termios)) == -1)
		error_exit("tcsetattr");
	tputs(tgetstr("vi", NULL), 1, ft_poutchar);
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("sc", NULL), 1, ft_poutchar);
}

void	exit_term(t_term *term)
{
	if (tcgetattr(term->fd, &term->termios) == -1)
		error_exit("tcgetattr");
	term->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(term->fd, TCSANOW, &(term->termios)) == -1)
		error_exit("tcsetattr");
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
}
