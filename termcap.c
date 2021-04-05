#include "minishell.h"

char    room_termtype[2048];
char    *termtype;
char    buf[100];
char    *buffer;

void	test_tgetnum(void)
{
	int	col;
	int	li;

	col = tgetnum("co");
	li = tgetnum("li");
	printf("Columns = %d, lines = %d\n", col, li);
}

int         ft_putint(int c)
{
   return (write(STDOUT_FILENO, &c, 1));
}

void		test_clean_screen(void)
{
   char    *clean_screen;
  
   buffer = buf;
   clean_screen = tgetstr("cl", &buffer);
  
   tputs(clean_screen, 1, ft_putint);
 
   buffer = buf;
   ft_bzero(buffer, 100);
}


int    termcap_test(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	termtype = getenv("TERM");
	if (termtype == NULL || (tgetent(room_termtype, termtype)) != 1)
		return (1);
	if (ft_strncmp(argv[1], "tgetnum", 7) == 0)
		test_tgetnum();
	else if (ft_strncmp(argv[1], "clear", 5) == 0)
		test_clean_screen();
	// else if (ft_strncmp(argv[1], "tgetflag", 8) == 0)
	// 	test_movement_nextline();
	return (0);
}