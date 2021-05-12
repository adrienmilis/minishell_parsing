#include "parser.h"

int main()
{
	char *cmd = "echo bonjour ||  echo salut";
	char **tab = ft_split(cmd, '|');
	int i = -1;
	while (tab[++i])
		printf("%d - %s\n", i, tab[i]);
	return (0);
}