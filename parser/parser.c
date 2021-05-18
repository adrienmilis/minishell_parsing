#include "parser.h"

void	doubleq_special(t_pars *p, char *cmd, t_pipe_cmd *p_begin, char **buff)
{	
	char	*tmp;

	if (cmd[p->i] == '$')
		*buff = ft_strjoin(*buff, get_variable(p, cmd, p_begin, 1));
	else if (cmd[p->i] == '\\')
	{
		p->i += 1;
		if (!(cmd[p->i] != '"' && cmd[p->i] != '\\' && cmd[p->i] != '$'))
		{
			*buff = ft_strjoin(*buff, ft_strdup("\\"));
			if (!(*buff))
				error_exit("malloc error", p_begin);
		}
		tmp = malloc(2 * sizeof(char));
		tmp[0] = cmd[p->i];
		tmp[1] = 0;
		*buff = ft_strjoin(*buff, tmp);
		if (!(*buff))
			error_exit("malloc error", p_begin);
		p->i += 1;
	}
}

char	*make_dquotes_arg(t_pars *p, char *cmd, t_pipe_cmd *p_begin)
{
	char	*buff;
	char	*tmp;
	int		start;

	start = p->i;
	buff = NULL;
	while (!(is_unesc_char(&cmd[p->i], p->i) && cmd[p->i] == '"'))
	{
		while (cmd[p->i] != '"' && cmd[p->i] != '\\' && cmd[p->i] != '$')
			p->i += 1;
		tmp = ft_strdup_len(cmd + start, p->i - start);
		if (!tmp)
			error_exit("malloc error", p_begin);
		buff = ft_strjoin(tmp, buff);
		if (!buff)
		{
			free(tmp);
			error_exit("malloc error", p_begin);
		}
		doubleq_special(p, cmd, p_begin, &buff);
	}
	return (buff);
}

void	arg_double_quotes(t_pars *p, t_pipe_cmd *p_begin, char *cmd)
{
	int		beg;
	char	*new_arg;

	beg = p->i;
	p->i += 1;
	new_arg = make_dquotes_arg(p, cmd, p_begin);
	if (beg != 0 && !is_r_space(&cmd[beg - 1], beg - 1))
	{
		if (!(append_arg(ft_lstlast(p_begin), new_arg, NULL)))
		{
			free(new_arg);
			error_exit("malloc error", p_begin);
		}
	}
	else
		add_argument(new_arg, p_begin, p, cmd);
	p->i += 1;
	p->in_d_quotes = 0;
}

void	in_double_quotes(t_pars *p, t_pipe_cmd *p_begin, char *cmd)
{
	if (cmd[p->i + 1] == '"')
	{
		p->i += 2;
		p->in_d_quotes = 0;
	}
	else
		arg_double_quotes(p, p_begin, cmd);
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
			out_quotes(&p, p_cmd_start, cmd);	// sortir IF in quote OR semicolon OR end of cmd
		else if (p.in_s_quotes)
			in_simple_quotes(&p, p_cmd_start, cmd);
		else
			in_double_quotes(&p, p_cmd_start, cmd);
	}
	reset_pars_struct(&p);
	print_list(p_cmd_start);
	return (p_cmd_start);
}
