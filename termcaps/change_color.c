#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <unistd.h>

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

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
	int 	ret;
	char	*tc;
	char	*reset_cmd;
	
	ret = init_term();
	if (ret == 0)
	{
		tc = tgetstr("AF", NULL);
		tputs(tparm(tc, COLOR_GREEN), 1, ft_putchar);
		printf("Phrase en vert !\n");
		printf("2eme phrase\n");

		reset_cmd = tgetstr("me", NULL);
		tputs(reset_cmd, 1, ft_putchar);
		
		printf("3eme phrase\n");
		tc = tgetstr("mb", NULL);
		tputs(tc, 1, ft_putchar);
		printf("Phrase clignotante\n");
		tputs(reset_cmd, 1, ft_putchar);
	}
	else
		printf("Termcaps init error!\n");
	return (0);
}