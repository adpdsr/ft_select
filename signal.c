/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:56:28 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 17:35:27 by adu-pelo         ###   ########.fr       */
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

static void	resize()
{

	static t_term	*term;

	term = NULL;
	term = ft_stock(term, 1);
	tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Effacer ecran et mettre curseur au debut
	//	display_interface(term);
	display_list(term);
}

static void	stop()
{
	t_term	*term;
	char	cp[2];

	term = NULL;
	term = ft_stock(term, 1);
	cp[0] = term->termios.c_cc[VSUSP];
	cp[1] = 0;
	term->termios.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, 0, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, cp);
}

static void	restart()
{
	t_term *term;

	term = NULL;
	term = ft_stock(term, 1);
	term->termios.c_lflag &= ~(ICANON | ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	tcsetattr(0, 0, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("vi", NULL), 1, ft_poutchar);
	signal(SIGTSTP, stop);
	display_list(term);
}

static void	end()
{
	t_term *term;

	term = NULL;
	term = ft_stock(term, 1);
	tcsetattr(0, TCSANOW, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
	exit(0);
}

void	catch_signal()
{
	signal(SIGWINCH, resize);
	signal(SIGTSTP, stop); // ctr_z
	signal(SIGCONT, restart);
	signal(SIGINT, end);
	signal(SIGQUIT, end);
}
