/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 11:17:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/03 16:54:32 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void error_exit(char *func)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(func, 2);
	exit(1);
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

#define BUFFER *(unsigned int *)buffer

void		get_key(t_term *term)
{
	int	ret = 0;
	char	buffer[5];

	ft_bzero(buffer, 5);
	read(0, buffer, 4); // protect read

	if (BUFFER == K_UP)
		up_arrow(term);
	if (BUFFER == K_LEFT)
		left_arrow(term);
	if (BUFFER == K_RIGHT)
		right_arrow(term);
	if (BUFFER == K_DOWN)
		down_arrow(term);
	if (BUFFER == K_SP)
		select_cur(term);
	if (BUFFER == K_ESC)
		escape(term);
	if (BUFFER == K_BSP)
		delete(term, &term->lst);
	display_list(term);
}

static void	check_args(int ac)
{
	if (ac < 2)
	{
		ft_putendl_fd("ft_select: usage: ./ft_select arg1 arg2 arg3 [...]", 2);
		exit(1);
	}
}

void	get_screen_size(t_term *term)
{
	ioctl(0, TIOCGWINSZ, &(term->win)); // Recupere la taille de la window et rempli la struct win
}

static void	init_term(t_term *term)
{
	if (!(term->name_term = getenv("TERM"))) // Recupere le nom du term
		error_exit("getenv");
	if (tgetent(NULL, term->name_term) < 1) // Check les cap du term avec name_term
		error_exit("tgetent");
	if (tcgetattr(0, &(term->termios)) == -1) // Recupere et rempli la structure termios
		error_exit("tcgetattr");
	term->termios.c_lflag &= ~(ICANON); // Met le terminal en mode canonique
	term->termios.c_lflag &= ~(ECHO); // Les touches tapees ne s'inscriront plus dans le term
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;
	get_screen_size(term);
	tputs(tgetstr("vi", NULL), 1, ft_poutchar); // Curseur invisible
	if (tcsetattr(0, TCSADRAIN, &(term->termios)) == -1) // on applique les changements
		error_exit("tcsetattr");
}

static void	exit_term(t_term *term)
{
	tputs(tgetstr("ve", NULL), 1, ft_poutchar); // Curseur normal visible
	term->termios.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &(term->termios)) == -1)
		error_exit("tcsetattr");
}

void		loop(t_term *term)
{
	tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Effacer l’écran et remettre le curseur au début
	display_list(term);
	while (1)
	{
		get_key(term);
	}
}

int			main(int ac, char **av)
{
	t_term term;

	term.lst = NULL;
	check_args(ac);
	init_term(&term);
	init_list(&term, av);
	loop(&term);
	exit_term(&term);
	return(0);
}
