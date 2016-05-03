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

static void error_exit(char *func)
{
	ft_putstr_fd("error: ", 2);
	ft_putendl_fd(func, 2);
	exit(1);
}

static void	check_args(int ac)
{
	ft_putendl("checking args"); // test

	if (ac < 2)
	{
		ft_putendl_fd("ft_select: usage: ./ft_select arg1 arg2 arg3 [...]", 2);
		exit(1);
	}
}

static void	init_term(t_term *term)
{
	ft_putendl("initializing term struct"); // test
	
	if (!(term->name_term = getenv("TERM"))) // recupere le nom du term
		error_exit("getenv");
	if (tgetent(NULL, term->name_term) < 1) // check les cap du term via name_term
		error_exit("tgetent");
	if (tcgetattr(0, &(term->termios)) == -1) // recupere et rempli la structure termios
		error_exit("tcgetattr");

	term->termios.c_lflag &= ~(ICANON); // met le terminal en mode canonique
	term->termios.c_lflag &= ~(ECHO); // les touches tapees ne s'inscriront plus dans le term
	term->termios.c_cc[VMIN] = 1;
	term->termios.c_cc[VTIME] = 0;

	ioctl(0, TIOCGWINSZ, &(term->win)); // recupere la taille de la window et rempli la struct win
	printf("ws_row |%d|\n", term->win.ws_row);			// test
	printf("ws_col |%d|\n", term->win.ws_col);			// test
	printf("ws_xpixel |%d|\n", term->win.ws_xpixel);	// test
	printf("ws_ypixel |%d|\n", term->win.ws_ypixel);	// test

	if (tcsetattr(0, TCSADRAIN, &(term->termios)) == -1) // on applique les changements
		error_exit("tcsetattr");
}

void		down_arrow(t_term *term)
{
	t_lst *tmp;

	ft_putendl("test1");
	tmp = term->lst;
	ft_putendl("test2");
	while (tmp->selected != 1)
	{
		ft_putendl("test3");
		tmp = tmp->next;
		ft_putendl("test4");
	}
	ft_putendl("test5");
	tmp->selected = 0;
	ft_putendl("test6");
	tmp->next->selected = 1;
	ft_putendl("test7");
}

void		get_key(t_term *term)
{
	int		ret = 0;
	char	buffer[5];

	ft_bzero(buffer, 5);
	read(0, buffer, 4);

	printf("keycode 1 = |%u|\n", *(unsigned int *)buffer);
	ret = tgetnum(buffer);
	printf("ret = |%d|\n", ret);
	if (*(unsigned int *)buffer == 4283163)
		ft_putendl("up arrow");
	if (*(unsigned int *)buffer == 4479771)
		ft_putendl("left arrow");
	if (*(unsigned int *)buffer == 4414235)
		ft_putendl("right arrow");
	if (*(unsigned int *)buffer == 4348699)
	{
		ft_putendl("down arrow");
		down_arrow(term);
	}
	//print_list(&(term->lst));
}

void		ft_select(t_term *term)
{
	tputs(tgetstr("cr", NULL), 1, ft_poutchar); // retour chariot
	tputs(tgetstr("sc", NULL), 1, ft_poutchar); // sauvegarder la position du curseur

	t_lst *tmp; // test
	while (1)
	{
		get_key(term);
		/* TEST */
		tmp = term->lst;
		while (tmp->next)
		{
			ft_putendl("test");
			tmp = tmp->next;
		}
	}
}

int			main(int ac, char **av)
{
	t_term term;

	check_args(ac);
	init_term(&term);
	init_list(term.lst, av);
	ft_select(&term);
	return(0);
}
