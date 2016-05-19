/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 13:56:28 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/19 12:53:36 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_select.h"

static void	resize(int sig)
{
	static t_term	*term;

	(void)sig;
	term = NULL;
	term = ft_stock(term, 1);
	tputs(tgetstr("rc", NULL), 1, ft_poutchar);
	tputs(tgetstr("cd", NULL), 1, ft_poutchar);
	display_list(term);
}

static void	stop(int sig)
{
	t_term	*term;
	char	cp[2];

	(void)sig;
	term = NULL;
	term = ft_stock(term, 1);
	cp[0] = term->termios.c_cc[VSUSP];
	cp[1] = 0;
	term->termios.c_lflag |= (ICANON | ECHO);
	tcsetattr(term->fd, TCSANOW, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
	signal(SIGTSTP, SIG_DFL);
	ioctl(0, TIOCSTI, cp);
}

static void	restart(int sig)
{
	t_term *term;

	(void)sig;
	term = NULL;
	term = ft_stock(term, 1);
	term->termios.c_lflag &= ~(ICANON | ECHO);
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	tcsetattr(term->fd, TCSANOW, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("vi", NULL), 1, ft_poutchar);
	signal(SIGTSTP, stop);
	display_list(term);
}

static void	end(int sig)
{
	t_term *term;

	(void)sig;
	term = NULL;
	term = ft_stock(term, 1);
	tcsetattr(term->fd, TCSANOW, &(term->termios));
	tputs(tgetstr("cl", NULL), 1, ft_poutchar);
	tputs(tgetstr("ve", NULL), 1, ft_poutchar);
	free_list(term);
	if (close(term->fd) < 0)
		error_exit("close");
	exit(0);
}

void		catch_signal(void)
{
	signal(SIGWINCH, resize);
	signal(SIGTSTP, stop);
	signal(SIGCONT, restart);
	signal(SIGQUIT, end);
	signal(SIGTERM, end);
	signal(SIGINT, end);
}
