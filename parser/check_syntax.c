#include "parser.h"

void set_quotes(int i, char *cmd, t_pars *p)
{
	if (!p->in_s_quotes && !p->in_d_quotes)			// si on est ni dans simple ni dans double
	{
		if (cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))	// si c'est une vraie simple
			p->in_s_quotes = 1;
		else if (cmd[i] == '\"' && (i == 0 || cmd[i - 1] != '\\')) // si c'est une vraie double
			p->in_d_quotes = 1;
	}
	else if (p->in_s_quotes && !p->in_d_quotes)	// si on est dans des simple quotes
	{
		if (cmd[i] == '\'' && (i == 0 || cmd[i - 1] != '\\'))	// si c'est une vraie simple
			p->in_s_quotes = 0;
	}
	else if (!p->in_s_quotes && p->in_d_quotes)	// si on est dans des double
		if (cmd[i] == '\"' && (i == 0 || cmd[i - 1] != '\\')) // si c'est une vraie double
			p->in_d_quotes = 0;
}

/* It assumes that quotes are closed (so this needs to be checked before) */

int	semicolons_valid(char *cmd)
{
	int		no_semicolon;
	int		i;
	t_pars	p;

	i = -1;
	no_semicolon = 1;
	init_pars_struct(&p);
	while (cmd[++i])
	{
		set_quotes(i, cmd, &p);
		if (no_semicolon == 1 && cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\')
			&& p.in_d_quotes == 0 && p.in_s_quotes == 0)
			return (0);
		if (!is_space(cmd[i]) && cmd[i] != ';')
			no_semicolon = 0;
		if (cmd[i] == ';' && (i == 0 || cmd[i - 1] != '\\'))
			no_semicolon = 1;
		if (cmd[i] == '|' || cmd[i] == '>' || cmd[i] == '<')
			no_semicolon = 1;
	}
	return (1);
}

int	pipes_valid(char *cmd)
{
	int		no_pipe;
	int		i;
	t_pars	p;

	i = -1;
	no_pipe = 1;
	init_pars_struct(&p);
	while (cmd[++i])
	{
		set_quotes(i, cmd, &p);
		if (no_pipe == 1 && cmd[i] == '|' && (i == 0 || cmd[i - 1] != '\\')
			&& p.in_d_quotes == 0 && p.in_s_quotes == 0)
			return (0);
		if (!is_space(cmd[i]) && cmd[i] != '|')
			no_pipe = 0;
		if (cmd[i] == '|' && (i == 0 || cmd[i - 1] != '\\'))
			no_pipe = 1;
		if (cmd[i] == ';' || cmd[i] == '>' || cmd[i] == '<')
			no_pipe = 1;
	}
	return (1);
}

int	quotes_are_closed(char *cmd)
{
	int		i;
	t_pars	p;

	i = -1;
	init_pars_struct(&p);
	while (cmd[++i])
		set_quotes(i, cmd, &p);
	if (p.in_s_quotes != 0 || p.in_d_quotes != 0)
		return (0);
	return (1);
}

void	check_syntax(char *cmd)
{
	if (!quotes_are_closed(cmd))
		error_exit("command ended while looking for matching quote", NULL);
	if (!semicolons_valid(cmd))
		error_exit("syntax error near unexpected token `;'", NULL);
	if (!pipes_valid(cmd))
		error_exit("syntax error near unexpected token `|'", NULL);
}