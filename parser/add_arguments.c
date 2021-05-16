#include "parser.h"

int	add_argument(t_pipe_cmd *p_cmd_curr, t_pars *p, char *cmd, char **tmp)
{
	int		i;
	char	**new_args;

	i = 0;
	if (p_cmd_curr->cmd)
		while (p_cmd_curr->cmd[i++])
			i++;
	new_args = malloc(sizeof(char *) * (i + 2));
	if (!new_args)
		return (0);
	i = 0;
	if (p_cmd_curr->cmd)
		while (p_cmd_curr->cmd[i])
		{
			new_args[i] = p_cmd_curr->cmd[i];
			i++;
		}
	new_args[i] = get_next_word(cmd, p);
	if (!new_args[i])
		return (0);
	new_args[i + 1] = 0;
	tmp = p_cmd_curr->cmd;
	p_cmd_curr->cmd = new_args;
	free(tmp);
	return (1);
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

char	*copy_next_word(char *cmd, t_pars *p, int word_size)
{
	char	*word;
	int		j;

	word = malloc(sizeof(char) * word_size);
	if (!word)
		return (NULL);
	j = 0;
	while (!is_r_space(&cmd[p->i], p->i) && !is_r_resvd_char(&cmd[p->i], p->i)
		&& !is_r_quote(&cmd[p->i], p->i) && cmd[p->i])
	{
		if (!(cmd[p->i] == '\\' && (is_space(cmd[p->i + 1])
			|| is_reserved_char(cmd[p->i + 1]) || is_quote(cmd[p->i + 1]))))
			word[j++] = cmd[p->i];
		(p->i)++;
	}
	word[j] = 0;
	return (word);
}

char	*get_next_word(char *cmd, t_pars *p)	// proteger le retour
{
	char	*word;
	int		j;
	int		escaped_space;

	escaped_space = 0;
	while (is_r_space(&cmd[p->i], p->i))
		p->i += 1;
	j = p->i;
	while (!is_r_space(&cmd[j], j) && !is_r_resvd_char(&cmd[j], j) && !is_r_quote(&cmd[j], j) && cmd[j])
	{
		if (is_space(cmd[j]) || is_reserved_char(cmd[j]))
			escaped_space++;
		j++;
	}
	word = copy_next_word(cmd, p, j - escaped_space - p->i + 1);
	return (word); // NULL en cas d'erreur
}