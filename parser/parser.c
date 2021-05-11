#include "parser.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	error_exit(char *msg)
{
	printf("minishell: %s\n", msg);
}

/* This function checks if semi-colons are well placed before splitting */

// !!!! encore des bugs !!!! ex : quand on ouvre des quotes et qu'on ne les ferme pas
// bien tester encore
int	is_valid_input(char *cmd)
{
	int	no_semicolon;
	int	i;
	int	in_double_quotes;
	int	in_simple_quotes;

	i = 0;
	no_semicolon = 1;
	in_double_quotes = 0;
	in_simple_quotes = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' && in_simple_quotes == 0 && in_double_quotes == 0)
			in_double_quotes = 1;
		if (cmd[i] == '\"' && in_simple_quotes == 0 && in_double_quotes == 1)
			in_double_quotes = 0;
		if (cmd[i] == '\'' && in_simple_quotes == 0 && in_double_quotes == 0)
			in_simple_quotes = 1;
		if (cmd[i] == '\'' && in_simple_quotes == 1 && in_double_quotes == 0)
			in_simple_quotes = 0;
		if (no_semicolon == 1 && cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\') && in_double_quotes == 0 && in_simple_quotes == 0)
			return (0);
		if (!is_space(cmd[i]) && cmd[i] != ';')
			no_semicolon = 0;
		if (cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\'))
			no_semicolon = 1;
		i++;
	}
	return (1);
}

void	parser(char *cmd)
{
	char	**tab;
	int		i;

	if (!is_valid_input(cmd))
		error_exit("syntax error near unepected token `;'");
	// split (!! il ne faut pas split sur les \; et les ; entre "" ou '' !!)
	i = 0;
	while (tab[i])
	{

		i++;
	}
}

int main(int argc, char **argv)
{
	char *str = argv[1];
	int ret = is_valid_input(str);
	printf("[%s]\n", str);
	if (ret == 1)
		printf("Valid command\n");
	else
		printf("Bad command\n");
	return (0);
}