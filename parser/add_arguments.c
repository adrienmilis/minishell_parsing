#include "parser.h"

void	add_argument(t_pipe_cmd *last, t_pipe_cmd *p_cmd_start, t_pars *p, char *cmd)
{
	int		i;
	char	**new_args;
	char	**tmp;
	char	*word;

	i = 0;
	if (last->cmd)
		while (last->cmd[i++])
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		error_exit("malloc error", p_cmd_start);
	i = 0;
	if (last->cmd)
		while (last->cmd[i])
		{
			new_args[i] = last->cmd[i];
			i++;
		}
	word = get_next_word(cmd, p, p_cmd_start);
	if (!word)
	{
		free(new_args);
		return ;
	}
	new_args[i] = word;
	new_args[i + 1] = 0;
	tmp = last->cmd;
	last->cmd = new_args;
	free(tmp);
}

int	append_arg(t_pipe_cmd *last, char *word)	// proteger le retour
{
	char	*new_arg;
	int		i;
	int		j;
	int		k;
	char 	*tmp;

	i = 0;
	while (last->cmd[i])
		i++;
	new_arg = malloc((ft_strlen(last->cmd[i - 1]) + ft_strlen(word) + 1)
				* sizeof(char)); // pb avec strlen si last->cmd est null
	if (!new_arg)
		return (0);
	j = 0;
	k = 0;
	while (last->cmd[i - 1][j])
		new_arg[k++] = last->cmd[i - 1][j++];
	j = 0;
	while (word[j])
		new_arg[k++] = word[j++];
	new_arg[k] = 0;
	tmp = last->cmd[i - 1];
	last->cmd[i - 1] = new_arg;
	free(tmp);
	return (1);
}

char	*copy_next_word(char *cmd, t_pars *p, int word_size, t_pipe_cmd *p_cmd_start)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * word_size);
	if (!word)
		error_exit("malloc error", p_cmd_start);
	j = 0;
	while (!is_r_space(&cmd[p->i], p->i) && !is_r_resvd_char(&cmd[p->i], p->i, 1)
		&& !is_r_quote(&cmd[p->i], p->i) && cmd[p->i])
	{
		if (!(cmd[p->i] == '\\' && !is_unesc_char(&cmd[p->i + 1], p->i + 1)))
			word[j++] = cmd[p->i];
		(p->i)++;
	}
	word[j] = 0;
	return (word);
}

char	*get_next_word(char *cmd, t_pars *p, t_pipe_cmd *p_cmd_start)	// renvoie NULL si on n'a rien trouve (mauvaise $var)
{
	char	*word;
	int		j;
	int		escaped;

	escaped = 0;
	while (is_r_space(&cmd[p->i], p->i))
		p->i += 1;
	if (cmd[p->i] == '$')
	{
		word = get_variable(p, cmd, p_cmd_start);
		return (word);
	}
	j = p->i;
	while (!is_r_space(&cmd[j], j) && !is_r_resvd_char(&cmd[j], j, 1) && !is_r_quote(&cmd[j], j) && cmd[j])
	{
		if (!is_unesc_char(&cmd[j], j))
			escaped++;
		j++;
	}
	word = copy_next_word(cmd, p, j - escaped - p->i + 1, p_cmd_start);
	return (word);
}
