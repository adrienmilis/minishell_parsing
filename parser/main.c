#include "parser.h"

char	**myenv;

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if ((!s1 && s2) || (s1 && !s2))
		return (1);
	while (s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

int main(int argc, char **argv, char **env)
{
	t_pipe_cmd	*pipe_cmd;

	myenv = new_env(env);
	pipe_cmd = parser("\"\\$PATH\"");	// NOT GOOD, corriger ça
	/*for (int k = 0; myenv[k] ; k++)
		printf("%s\n", myenv[k]);*/
	free_pipe_cmd(pipe_cmd);
}