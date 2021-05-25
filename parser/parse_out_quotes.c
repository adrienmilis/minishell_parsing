#include "parser.h"

// char	*get_redir_file(t_pars *p, char *cmd, t_pars *p_begin)
// {
// 	char	*word;

// 	while (is_space(cmd[p->i]))
// 		p->i += 1;
// 	if (cmd[p->i] == '\'')

// 	else if (cmd[p->i] == '\"')

// 	else
// 		word = get_next_word(cmd, p, p_begin);
// 	return (word);
// }

void	real_sign2(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd, char sign)
{
	char		*word;
	t_pipe_cmd	*last;
	int			fd;

	last = ft_lstlast(p_cmd_start);
	word = get_next_word(cmd, p, p_cmd_start);
	//word = get_redir_file(p, cmd, p_cmd_start);
	if (sign == '>')
	{
		if (!word)
			error_exit("syntax error near unexpected token `>'", p_cmd_start); // pas de leak si on exit sans free word ??
		if (last->output)
			free(last->output);
		fd = open(word, O_RDONLY | O_CREAT, 0644);
		close(fd);
		last->output = word;
		return ;
	}
	if (sign == '<')
	{
		if (!word)
			error_exit("syntax error near unexpected token `<'", p_cmd_start); // pas de leak si on exit sans free word ??
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

void	out_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd)
{
	char	*word;

	if (is_r_resvd_char(&cmd[p->i], p->i, 0))
		reserved_chars(p, p_cmd_start, cmd);
	else if (is_r_space(&cmd[p->i], p->i))
	{
		p->i += 1;
		out_quotes(p, p_cmd_start, cmd);
	}
	else if (cmd[p->i] == '\'')
		p->in_s_quotes = 1;
	else if (cmd[p->i] == '"')
		p->in_d_quotes = 1;
	else if (p->i != 0 && !is_r_space(&cmd[p->i - 1], p->i - 1) && !is_r_resvd_char(&cmd[p->i - 1], p->i - 1, 0))
	{
		word = get_next_word(cmd, p, p_cmd_start);
		if (word)
			if (!append_arg(ft_lstlast(p_cmd_start), word, NULL))
				error_exit("malloc error", p_cmd_start);
	}
	else	// on est au debut d'un mot et pas de quote avant
	{
		word = get_next_word(cmd, p, p_cmd_start);
		add_argument(word, p_cmd_start);
	}
}
