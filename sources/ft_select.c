/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 11:17:30 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/11/09 14:15:35 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	check_args(int ac)
{
	if (ac < 2)
	{
		ft_putendl_fd("ft_select: usage: ./ft_select arg1 arg2 arg3 ...", 2);
		exit(1);
	}
}

static void	get_key(t_term *term)
{
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

static void	loop(t_term *term)
{
	get_size_info(term);
	term = ft_stock(term, 0);
	display_list(term);
	while (1)
	{
		get_key(term);
		tputs(tgetstr("rc", NULL), 1, ft_poutchar);
		tputs(tgetstr("cd", NULL), 1, ft_poutchar);
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
	return (0);
}
