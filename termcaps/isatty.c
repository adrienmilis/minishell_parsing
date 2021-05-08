#include <unistd.h>
#include <stdio.h>

int main()
{
	int		ret;
	char	buf[100];
	int		term_fd;

	term_fd = ttyslot();
	ret = isatty(term_fd);
	if (ret == 1)
	{
		printf("Fd %d is a tty\n", term_fd);
		printf("ttyname : %s\n", ttyname(0));
	}
	else
		printf("Fd  is not a tty\n");
	return (0);
}