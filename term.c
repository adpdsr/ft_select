#include "ft_select.h"

void     init_term(t_term *term)
{
          if (!(term->name_term = getenv("TERM")))
                  error_exit("getenv");
          if (tgetent(NULL, term->name_term) < 1)
                  error_exit("tgetent");
          if (tcgetattr(0, &(term->termios)) == -1)
                  error_exit("tcgetattr");
          term->termios.c_lflag &= ~(ICANON);
          term->termios.c_lflag &= ~(ECHO);
          term->termios.c_cc[VMIN] = 1;
          term->termios.c_cc[VTIME] = 0;
          ioctl(0, TIOCGWINSZ, &(term->win));
          tputs(tgetstr("vi", NULL), 1, ft_poutchar); // Curseur invisible
          if (tcsetattr(0, TCSADRAIN, &(term->termios)) == -1) // on applique les changements
                 error_exit("tcsetattr");
}       
          
void     exit_term(t_term *term)
{       
          tputs(tgetstr("ve", NULL), 1, ft_poutchar); // Curseur normal visible
          term->termios.c_lflag |= (ICANON | ECHO);
          if (tcsetattr(0, 0, &(term->termios)) == -1)
                  error_exit("tcsetattr");
}
