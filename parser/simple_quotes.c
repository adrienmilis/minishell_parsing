#include "parser.h"

void	arg_simple_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	int		beg;
	int		start;
	char	*new_arg;

	beg = p->i;
	p->i += 1;
	start = p->i;
	while (cmd[p->i] != '\'')
		p->i += 1;
	new_arg = ft_strdup_len(cmd + start, p->i - start);
	if (!new_arg)
		error_exit("malloc error", p_cmd_start);
	if (beg != 0 && !is_r_space(&cmd[beg - 1], beg - 1))
	{
		if (!(append_arg(ft_lstlast(p_cmd_start), new_arg, NULL)))
		{
			free(new_arg);
			error_exit("malloc error", p_cmd_start);
		}
	}
	else
		add_argument(new_arg, p_cmd_start);
	p->i += 1;
	p->in_s_quotes = 0;
}

void	in_simple_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	if (cmd[p->i + 1] == '\'')
	{
		p->i += 2;
		p->in_s_quotes = 0;
	}
	else
		arg_simple_quotes(p, p_cmd_start, cmd);
}