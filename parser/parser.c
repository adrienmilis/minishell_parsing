#include "parser.h"

int	append_arg(char **args, char *word)	// proteger le retour
{
	char	*new_arg;
	int		i;
	int		j;
	int		k;
	char 	*tmp;

	i = 0;
	while (args[i])
		i++;
	new_arg = malloc((ft_strlen(args[i - 1]) + ft_strlen(word) + 1)
				* sizeof(char));
	if (!new_arg)
		return (0);
	j = 0;
	k = 0;
	while (args[i - 1][j])
		new_arg[k++] = args[i - 1][j++];
	j = 0;
	while (word[j])
		new_arg[k++] = word[j++];
	new_arg[k] = 0;
	tmp = args[i - 1];
	args[i - 1] = new_arg;
	free(tmp);
	return (1);
}

char	*get_next_word(char *cmd, int *i)	// proteger le retour
{
	char	*word;
	int		j;

	j = *i;
	while (!is_space(cmd[j]) && !is_reserved_word(cmd[j])
		&& cmd[j] != '\'' && cmd[j] != '\"')
		j++;
	word = malloc(sizeof(char) * (j + 1));
	if (!word)
		return (NULL);
	while (!is_space(cmd[*i]) && !is_reserved_word(cmd[*i])
		&& cmd[*i] != '\'' && cmd[*i] != '\"')
	{
		word[*i] = cmd[*i];
		*i++;
	}
	word[*i] = 0;
	return (word);
}

/*	si on ne commence pas par un whitespace, il faut append au dernier argument (sauf si i == 0). 
	Sinon, en créer un nouveau */

void	parse_out_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, int *i, char *cmd)
{
	t_pipe_cmd	*last_elem;
	char		*word;

	last_elem = ft_lstlast(p_cmd_start);
	if (is_reserved_word(cmd[*i]))
	{
		// ; --> parsing is finished
		// | --> new elem added to list
		// > --> get next word IF there is one, 
	}
	else if (is_space(cmd[*i]))
	{
		// new argument OR reserved char OR quote
	}
	else if (cmd[*i] == '\'' || cmd[*i] == '\"')
	{

	}
	else if (cmd[*i] == '<' || cmd[*i] == '>')
	{

	}
	else if (*i != 0) // append
	{
	
		word = get_next_word(cmd, i);
		if (!word)
			// error free
		if (!append_arg(last_elem->cmd, word));
			// error free
	}
	else
	{

	}
	if (p->in_d_quotes == 1 || p->in_s_quotes == 1 || p->semicolon == 1 || cmd[*i])
		return ;
}

void	parse_in_quotes(t_pars *p, t_pipe_cmd *pipe_cmd, int *i, char *cmd)
{
	/* si on ne commence pas par un whitespace, il faut append au dernier argument (sauf si i == 0). 
	Sinon, en créer un nouveau */

	if ((p->in_d_quotes == 0 && p->in_s_quotes == 0) || cmd[*i])
		return ;
}

t_pipe_cmd	*parser(char *cmd)
{
	t_pipe_cmd		p_cmd_start;
	t_pars			p;
	static int		i;

	check_syntax(cmd);
	init_pars_struct(&p);
	while (p.semicolon == 0 && cmd[i])
	{
		if (p.in_d_quotes == 0 && p.in_s_quotes == 0)
			parse_out_quotes(&p, &p_cmd_start, &i, cmd);	// sortir IF in quote OR semicolon OR end of cmd
		else
			parse_in_quotes(&p, &p_cmd_start, &i, cmd);	// sortir IF end quote OR end of cmd
	}
	return (&p_cmd_start);
}
