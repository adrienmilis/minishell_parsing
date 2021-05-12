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

/* 	This function checks if semi-colons are well placed before splitting 
	It assumes that quotes are closed (so this needs to be checked before) */

int	in_quotes()
{
	
}

int	semicolons_valid(char *cmd)
{
	int	no_semicolon;
	int	i;
	int	in_double_quotes;
	int	in_simple_quotes;

	i = -1;
	no_semicolon = 1;
	in_double_quotes = 0;
	in_simple_quotes = 0;
	while (cmd[++i])
	{
		// if (cmd[i] == '\"' && in_simple_quotes == 0 && in_double_quotes == 0)
		// 	in_double_quotes = 1;
		// if (cmd[i] == '\"' && in_simple_quotes == 0 && in_double_quotes == 1)		// FAUX, a changer
		// 	in_double_quotes = 0;
		// if (cmd[i] == '\'' && in_simple_quotes == 0 && in_double_quotes == 0)
		// 	in_simple_quotes = 1;
		// if (cmd[i] == '\'' && in_simple_quotes == 1 && in_double_quotes == 0)
		// 	in_simple_quotes = 0;
		if (no_semicolon == 1 && cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\') && in_double_quotes == 0 && in_simple_quotes == 0)
			return (0);
		if (!is_space(cmd[i]) && cmd[i] != ';')
			no_semicolon = 0;
		if (cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\'))
			no_semicolon = 1;
	}
	return (1);
}

void check_in_quotes(int i, char *cmd, int *in_s_quotes, int *in_d_quotes)
{
	if (*in_s_quotes == 0 && *in_d_quotes == 0)			// si on est ni dans simple ni dans double
	{
		if (cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))	// si c'est une vraie simple
			*in_s_quotes = 1;
		else if (cmd[i] == '\"' && (i == 0 || cmd[i - 1] != '\\')) // si c'est une vraie double
			*in_d_quotes = 1;
	}
	else if (*in_s_quotes == 1 && *in_d_quotes == 0)	// si on est dans des simple quotes
	{
		if (cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))	// si c'est une vraie simple
			*in_s_quotes = 0;
	}
	else if (*in_s_quotes == 0 && *in_d_quotes == 1)	// si on est dans des double
		if (cmd[i] == '\"' && (i == 0 || cmd[i - 1] != '\\')) // si c'est une vraie double
			*in_d_quotes = 0;
}

int	quotes_are_closed(char *cmd)
{
	int	i;
	int	in_simple_quotes;
	int	in_double_quotes;

	i = -1;
	in_simple_quotes = 0;
	in_double_quotes = 0;
	while (cmd[++i])
		check_in_quotes(i, cmd, &in_simple_quotes, &in_double_quotes);
	if (in_simple_quotes != 0 || in_double_quotes != 0)
		return (0);
	return (1);
}

void	parser(char *cmd)
{
	char	**tab;
	int		i;

	if (!quotes_are_closed(cmd))
		error_exit("command ended while looking for matching quote");
	if (!semicolons_valid(cmd))
		error_exit("syntax error near unepected token `;'");
	// split (!! il ne faut pas split sur les \; et les ; entre quotes !!)
	// et ne pas ajouter les espaces superflus ??
	i = 0;
	while (tab[i])
	{

		i++;
	}
}
