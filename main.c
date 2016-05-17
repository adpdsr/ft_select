/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 11:17:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 16:12:50 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	get_key(t_term *term)
{
	int		ret = 0;
	char	buffer[5];

	ft_bzero(buffer, 5);
	if (read(0, buffer, 4) < 0)
		error_exit("read");
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
	if (BUFFER == K_BSP || BUFFER == K_DEL)
		del(term, &term->lst);
	if (BUFFER == K_RET)
		ret_to_shell(term);
}

static void	check_args(int ac)
{
	if (ac < 2)
	{
		ft_putendl_fd("ft_select: usage: ./ft_select arg1 arg2 arg3 [...]", 2);
		exit(1);
	}
}

void			display_interface(t_term *term)
{
	int i = 0;
	char *title = "ft_select";
	int start;
	int len;

	/**/
	len = term->info.nb_col;
	while (len)
	{
		ft_putchar_fd('-', 2);
		len--;
	}
	ft_putchar_fd('\n', 2);
	/**/
	len = term->info.nb_col;
	start = (len / 2) - 5;
	while (start)
	{
		ft_putchar(' ');
		start--;
	}
	while (title[i])
	{
		ft_putchar_fd(title[i], 2);
		usleep((unsigned int) 100000);
		i++;
	}
	ft_putchar_fd('\n', 2);
	/**/
	len = term->info.nb_col;
	while (len)
	{
		ft_putchar_fd('-', 2);
		len--;
	}
	/**/
	ft_putchar_fd('\n', 2);
}

static void		loop(t_term *term)
{
	get_size_info(term);
	tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Effacer ecran et mettre curseur au debut
//	display_interface(term);
	tputs(tgetstr("sc", NULL), 1, ft_poutchar); // Enregistre la position du curseur
	term = ft_stock(term, 0);
	display_list(term);
	while (1)
	{
		get_key(term);
		tputs(tgetstr("rc", NULL), 1, ft_poutchar); // Restaurer la position enregistrée du curseur
		tputs(tgetstr("cd", NULL), 1, ft_poutchar); // Effacer jusqu’à la fin de l’écran
		//tputs(tgetstr("cl", NULL), 1, ft_poutchar); // Effacer ecran et mettre curseur au debut
		//display_interface(term);
		display_list(term);
	}
}

int			main(int ac, char **av)
{
	t_term term;

	check_args(ac);
	catch_signal();
	init_term(&term);
	init_list(&term, av);
	loop(&term);
	return(0);
}
