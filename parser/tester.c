#include "parser.h"

int main(int argc, char **argv)
{
	char 	valid_cmds[5][100] = 
	{
		"echo bonjour",
		"echo salut",
		NULL
	};
	char	unvalid_cmds[5][100] =
	{
		"; echo bonjour",
		"echo ; ; salut",
		0
	};
	int i = 0;
	while (valid_cmds[i])
	{
		if (!is_valid_command(valid_cmds[i]))
			printf("Should be valid : [%s]\n", valid_cmds[i]);
		i++;
	}
	i = 0;
	while (unvalid_cmds[i])
	{
		if (is_valid_command(unvalid_cmds[i]))
			printf("Should be unvalid : [%s]\n", unvalid_cmds[i]);
		i++;
	}
	return (0);
}