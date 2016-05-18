/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adu-pelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 10:46:12 by adu-pelo          #+#    #+#             */
/*   Updated: 2016/05/17 18:44:28 by adu-pelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT

# include "../libft/libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include <signal.h>
# include <fcntl.h>
# include <term.h>

/* KEY CODES */

# define K_DEL 2117294875
# define K_RIGHT 4414235
# define K_LEFT	4479771
# define K_DOWN 4348699
# define K_UP 4283163
# define K_BSP 127
# define K_RET 10
# define K_ESC 27
# define K_SP 32

/* ANSI COLORS */

# define MAGENTA "\033[35m"
# define YELLOW "\033[33m"
# define GREEN "\033[32m"
# define WHITE "\033[37m"
# define RESET "\033[00m"
# define BLACK "\033[30m"
# define BLUE "\033[34m"
# define CYAN "\033[36m"
# define RED "\033[31m"

# define BUFFER *(unsigned int *)buffer

typedef struct winsize t_win;
typedef struct termios t_tcpy;

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
	int				fd;
	t_win			win;
	t_lst			*lst;
	t_size			info;
	t_tcpy			termios;
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
void			get_size_info(t_term *term);
int         	check_size(t_term *term);
t_term			*ft_stock(t_term *term, int i);

void			free_list(t_term *term);
void			display_list(t_term *term);
void			init_list(t_term *term, char **av);
int				set_display(t_term *term, int pos_col, int i);
t_lst			*list_position(t_lst **head);

void 			error_exit(char *func);
void			catch_signal(void);
int				ft_poutchar(int c);

#endif
