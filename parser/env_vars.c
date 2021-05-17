#include "parser.h"

char 	*unvalid_var_name(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start)
{
	char	*word;
	int		i;
	int		j;
	char	*tmp_word;

	if (is_space(cmd[p->i]) || cmd[p->i] == 0)
	{
		tmp_word = ft_strdup("$");
		if (!tmp_word)
			error_exit("malloc error", p_cmd_start);
		return (tmp_word);
	}
	tmp_word = get_next_word(cmd, p, p_cmd_start);
	word = malloc(sizeof(char) * (ft_strlen(tmp_word) + 2));
	if (!word)
		error_exit("malloc error", p_cmd_start);
	i = 1;
	j = 0;
	word[0] = '$';
	while (tmp_word[i - 1])
		word[i++] = tmp_word[j++];
	word[i] = 0;
	free(tmp_word);
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

char	*get_variable(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start)
{
	char	*tmp_word;
	char	*word;

	p->i += 1;
	if (is_number(cmd[p->i]))
	{
		p->i += 1;
		return (NULL);
	}
	if (!valid_var_char(cmd[p->i]))
		word = unvalid_var_name(p, cmd, p_cmd_start);
	else
		word = valid_var_name(p, cmd, p_cmd_start);
	return (word);
}