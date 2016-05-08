/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:46:12 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/03 16:54:35 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include "libft/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <stdio.h> // test
# include <term.h>

# define K_UP 4283163	
# define K_LEFT	4479771	
# define K_RIGHT 4414235
# define K_DOWN 4348699
# define K_DEL 2117294875
# define K_SP 32
# define K_RET 10
# define K_ESC 27
# define K_BSP 127

typedef struct		s_lst
{
	int 		pos;
	int		selected;
	int		id;
	int		len;
	char		*name;
	struct s_lst	*next;
	struct s_lst	*prev;
}			t_lst;

typedef struct		s_term
{
	struct winsize	win;
	struct termios	termios;
	char		*name_term;
	t_lst		*lst;	
}			t_term;

void            escape(t_term *term);
void            select_cur(t_term *term);
void            del(t_term *term, t_lst **head);
void            up_arrow(t_term *term);
void            down_arrow(t_term *term);
void            left_arrow(t_term *term);
void            right_arrow(t_term *term);
void    	init_term(t_term *term);
void   	  	exit_term(t_term *term);
void		init_list(t_term *term, char **av);
void		display_list(t_term *term);
//void		free_list(t_term *term);

int		ft_poutchar(int c);
void 		error_exit(char *func);
t_lst		*list_position(t_lst **head);

#endif
