/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:46:12 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/10 17:32:01 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include "libft/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <term.h>

# define BUFFER *(unsigned int *)buffer

/* KEYBOARD CODES */

# define K_DEL 2117294875
# define K_RIGHT 4414235
# define K_LEFT	4479771
# define K_DOWN 4348699
# define K_UP 4283163
# define K_BSP 127
# define K_RET 10
# define K_ESC 27
# define K_SP 32

/* ANSI COLOR CODES */

# define MAGENTA "\033[35m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"
# define WHITE "\033[37m"
# define RESET "\033[00m"
# define BLACK "\033[30m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"

typedef struct		s_lst
{
	int 			pos;
	int				selected;
	int				id;
	int				len;
	char			*name;
	struct s_lst	*next;
	struct s_lst	*prev;
}					t_lst;

typedef struct		s_size_info
{
	int				nb_elem;
	int				max_len;
	int				nb_col;
	int				nb_row;
}					t_size;

typedef struct		s_term
{
	char			*name_term;
	struct winsize	win;
	struct termios	termios;
	t_size			info;
	t_lst			*lst;
}					t_term;

void            escape(t_term *term);
void            select_cur(t_term *term);
void			ret_to_shell(t_term *term);
void            del(t_term *term, t_lst **head);
void            up_arrow(t_term *term);
void            down_arrow(t_term *term);
void            left_arrow(t_term *term);
void            right_arrow(t_term *term);

void    		init_term(t_term *term);
void   	  		exit_term(t_term *term);
void			init_list(t_term *term, char **av);
void			display_list(t_term *term);
void			get_size_info(t_term *term);
//void			free_list(t_term *term);

int				ft_poutchar(int c);
void 			error_exit(char *func);
t_lst			*list_position(t_lst **head);

int		set_display(t_term *term, int pos_col, int i);

#endif
