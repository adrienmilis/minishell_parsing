#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>

/* FONCTIONS AUTORISEES :
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs */

int init_term()
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
		return (-1);
	ret = tgetent(NULL, term_type);
	if (ret == 0 || ret == -1)
		return (-1);
	return (0);
}

int main()
{
	int	ret;

	ret = init_term();
	if (ret == 0)
		printf("Success !\n");
	else
		printf("Error !\n");
}