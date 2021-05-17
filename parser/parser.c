#include "parser.h"

void	parse_in_quotes(t_pars *p, t_pipe_cmd *pipe_cmd, char *cmd)
{
	

	if ((!p->in_d_quotes && !p->in_s_quotes) || cmd[p->i])
		return ;
}

t_pipe_cmd	*parser(char *cmd)
{
	t_pipe_cmd		*p_cmd_start;
	static t_pars	p;

	if (!cmd || !cmd[0])
		return (NULL);
	check_syntax(cmd);
	init_pars_struct(&p);
	p_cmd_start = init_pipe_list();
	while (!p.semicolon && cmd[p.i])
	{
		if (!p.in_d_quotes && !p.in_s_quotes)
			parse_out_quotes(&p, p_cmd_start, cmd);	// sortir IF in quote OR semicolon OR end of cmd
		else
			parse_in_quotes(&p, p_cmd_start, cmd);	// sortir IF end quote OR end of cmd
	}
	reset_pars_struct(&p);
	print_list(p_cmd_start);
	return (p_cmd_start);
}
