#include "parser.h"

char 	*unvalid_var_name(t_pars *p, char *cmd, t_pipe_cmd *p_begin, char *tmp)
{
	char	*word;
	int		i;
	int		j;
	// char	*tmp_word;

	if (is_space(cmd[p->i]) || cmd[p->i] == 0)
	{
		if (tmp)
			free (tmp);
		tmp = ft_strdup("$");
		if (!tmp)
			error_exit("malloc error", p_begin);
		return (tmp);
	}
	// tmp_word = get_next_word(cmd, p, p_cmd_start);
	word = malloc(sizeof(char) * (ft_strlen(tmp) + 2));
	if (!word)
		error_exit("malloc error", p_begin);
	i = 1;
	j = 0;
	word[0] = '$';
	while (tmp[i - 1])
		word[i++] = tmp[j++];
	word[i] = 0;
	free(tmp);
	return (word);
}

char	*get_env_var(int index)
{
	char	*var_value;
	int		j;

	j = 0;
	while (myenv[index][j] != '=' && myenv[index][j])
		j++;
	var_value = ft_strdup(myenv[index] + j + 1);
	if (!var_value)
		return (NULL);
	return (var_value);
}

char	*valid_var_name(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start)
{
	char 	*var_name;
	int		start;
	int		j;
	char 	*var_value;

	j = 0;
	start = p->i;
	while (valid_var_char(cmd[p->i]))
		p->i += 1;
	var_name = ft_strdup_len(cmd + start, p->i - start);
	if (!var_name)
		error_exit("malloc error", p_cmd_start);
	while (myenv[j] && strcmp_env(var_name, myenv[j]))
		j++;
	if (myenv[j] == 0)
		return (NULL);
	free(var_name);
	var_value = get_env_var(j);
	if (!var_value)
		error_exit("malloc error", p_cmd_start);
	return (var_value);
}

char	*gnw_double_quotes(t_pars *p, char *cmd, t_pipe_cmd *p_begin)
{
	char	*word;
	int		start;

	start = p->i;
	while (!is_space(cmd[p->i]) && cmd[p->i] != '"')
		p->i++;
	word = ft_strdup_len(cmd + start, p->i - start);
	if (!word)
		error_exit("malloc error", p_begin);
	return (word);
}

char	*get_variable(t_pars *p, char *cmd, t_pipe_cmd *p_begin, int d_quotes)
{
	char	*tmp;
	char	*word;

	p->i += 1;
	if (is_number(cmd[p->i]))
	{
		p->i += 1;
		return (NULL);
	}
	if (!valid_var_char(cmd[p->i]))
	{
		if (d_quotes == 1)	// gnw jusque espace ou ""
			tmp = gnw_double_quotes(p, cmd, p_begin);
		else	// gnw classique
			tmp = get_next_word(cmd, p, p_begin);
		word = unvalid_var_name(p, cmd, p_begin, tmp);
	}
	else
		word = valid_var_name(p, cmd, p_begin);
	return (word);
}