#include "parser.h"

void	real_sign2(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd, char sign)
{
	char		*word;
	t_pipe_cmd	*last;
	int			fd;

	last = ft_lstlast(p_cmd_start);
	word = get_next_word(cmd, p);
	if (!word)
		error_exit("malloc error", p_cmd_start);
	if (sign == '>')
	{
		if (last->output)
			free(last->output);
		fd = open(word, O_CREAT, 0644);
		close(fd);
		last->output = word;
	}
	if (sign == '<')
	{
		if (last->input)
			free(last->input);
		last->input = word;
	}
}

void	real_sign(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	t_pipe_cmd	*last;
	char		sign;

	sign = cmd[p->i];
	last = ft_lstlast(p_cmd_start);
	if (cmd[p->i] == '>')
	{
		if (cmd[p->i + 1] == '>')
		{
			p->i += 1;
			last->double_greater = 1;
		}
		else
			last->double_greater = 0;
	}
	p->i += 1;
	real_sign2(p, p_cmd_start, cmd, sign);
}

void	reserved_chars(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	t_pipe_cmd	*n_elem;

	if (cmd[p->i] == ';')
	{
		p->semicolon = 1;
		p->i += 1;
		return ;
	}
	else if (cmd[p->i] == '>' || cmd[p->i] == '<')
		real_sign(p, p_cmd_start, cmd);
	else if (cmd[p->i] == '|')
	{
		n_elem = new_elem();
		if (!n_elem)
			error_exit("malloc error", p_cmd_start);
		ft_lstadd_back(&p_cmd_start, n_elem);
		p->i += 1;
	}
}

void	parse_out_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	t_pipe_cmd	*last_elem;
	char		*word;

	last_elem = ft_lstlast(p_cmd_start);
	if (is_r_resvd_char(&cmd[p->i], p->i))
		reserved_chars(p, p_cmd_start, cmd);
	else if (is_r_space(&cmd[p->i], p->i))
	{
		p->i += 1;
		parse_out_quotes(p, p_cmd_start, cmd);
	}
	else if (cmd[p->i] == '\'')
		p->in_s_quotes = 1;
	else if (cmd[p->i] == '"')
		p->in_d_quotes = 1;
	else if (p->i != 0 && is_r_quote(&cmd[p->i - 1], p->i - 1)) // append si c'est direct le debut d'un mot qd on rentre ds la fonction SAUF SI on apl la fonction apres un unescaped space !!
	{
		word = get_next_word(cmd, p);
		if (!word || !append_arg(last_elem, word))
			error_exit("malloc error", p_cmd_start);
	}
	else	// on est au debut d'un mot et pas de quote avant
		if (!add_argument(last_elem, p, cmd, NULL))
			error_exit("malloc error", p_cmd_start);
}