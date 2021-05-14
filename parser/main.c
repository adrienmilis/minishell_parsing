#include "parser.h"

int main(int argc, char **argv)
{
	int i = 0;

	char **tab;
	tab = malloc(3 * sizeof(char*));
	tab[2] = 0;
	tab[0] = "hello";
	tab[1] = "salut";
	char *word = " coucou";
	while (tab[i])
		printf("%s\n", tab[i++]);
	printf("-----\n");
	append_arg(tab, word);
	i = 0;
	while (tab[i])
		printf("%s\n", tab[i++]);
}