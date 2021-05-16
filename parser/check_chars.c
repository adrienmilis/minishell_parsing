#include "parser.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_r_space(char *c, int i)
{
	if (!is_space(*c))
		return (0);
	if (i == 0 || *(c - 1) != '\\')
		return (1);
	return (0);
}

int	is_reserved_char(char c)
{
	if (c == '|' || c == ';' || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_r_resvd_char(char *c, int i)
{
	if (!is_reserved_char(*c))
		return (0);
	if (i == 0 || *(c - 1) != '\\')
		return (1);
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_r_quote(char *c, int i)
{
	if (!is_quote(*c))
		return (0);
	if (i == 0 || *(c - 1) != '\\')
		return (1);
	return (0);
}