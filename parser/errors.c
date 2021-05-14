#include "parser.h"

void	error_exit(char *msg)
{
	printf("minishell: %s\n", msg);
	exit(0);
}