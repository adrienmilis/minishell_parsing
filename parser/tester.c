#include "parser.h"

void semicolon_tester()
{
	printf("---SEMICOLONS TESTER---\n");
	char 	valid_cmds[5][100] = 
	{
		"echo bonjour",
		"echo ; ",
		"echo \" ; \" ; echo",
		"echo ' ; ' ; echo"
	};
	char	unvalid_cmds[5][100] =
	{
		"; echo bonjour",
		"echo ; ; salut",
		"echo bonjour ;		;",
		"echo ;; bonjour",
	};
	int i = 0;
	int	nb_of_valids = 4;
	int	nb_of_invalids = 4;
	while ( i < nb_of_valids /*valid_cmds[i]*/)
	{
		if (!semicolons_valid(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_invalids /*unvalid_cmds[i]*/)
	{
		if (semicolons_valid(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
}

void	quotes_tester()
{
	printf("---QUOTES TESTER---\n");
	char 	valid_cmds[50][100] = 
	{
		"echo \"bonjour\"",
		"echo \'salut\'",
		"echo \"bonjour\' \' \' salut\"",
		"echo \'bonjour \"\"\" salut \'",
		"echo \"\"\"bonjour\"",
		"echo \\\' salut",
		"ec\"ho\" bjr slt",
		"echo \" \' \' \\\" \\\" \\\" \' \' \' \" \'\'"
	};
	char	unvalid_cmds[50][100] =
	{
		"echo \'bonjour\'\'",
		"echo \'",
		"echo \"",
		"echo \' salut \' \'",
		"echo \" salut \" \"",
		"echo \" \' \' \\\" \\\" \\\" \' \' \' \" \'\' \""
	};
	int i = 0;
	int	nb_of_valids = 8;
	int	nb_of_invalids = 6;
	while ( i < nb_of_valids)
	{
		if (!quotes_are_closed(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (i < nb_of_invalids)
	{
		if (quotes_are_closed(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
}

int main()
{
	semicolon_tester();
	quotes_tester();
}