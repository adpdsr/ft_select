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
# include <term.h>

# include <stdio.h> // test

# define K_UP 4283163		// fleche haut
# define K_LEFT	4479771		// fleche gauche
# define K_RIGHT 4414235	// fleche droite
# define K_DOWN 4348699		// fleche bas
# define K_SP 32			// space
# define K_RET 10			// return
# define K_ESC 27			// escape
# define K_DEL 2117294875	// delete
# define K_BSP 127			// backspace

typedef struct		s_lst // list for ags
{
	int 			first;
	int				selected;	// bool, 1 if selected, else 0
	int				len;		// len of arg
	char			*name;		// name of arg
	struct s_lst	*next;
}					t_lst;

typedef struct		s_term
{
	struct winsize	win;
	struct termios	termios;
	char			*name_term;
	t_lst			*lst;	
}					t_term;

void	init_list(t_lst *lst, char **av);

int		ft_poutchar(int c);

void	print_list(t_lst **head); // test

#endif
