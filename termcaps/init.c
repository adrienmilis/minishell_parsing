#include <stdlib.h>
#include <curses.h>
#include <term.h>
#include <stdio.h>

int main()
{
	int ret;

	// ret = tgetent(NULL, getenv("TERM"));
	tgetflag("test");
	return (0);
}