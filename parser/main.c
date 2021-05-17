#include "parser.h"

char	**myenv;

int main(int argc, char **argv, char **env)
{
	t_pipe_cmd	*pipe_cmd;

	myenv = new_env(env);
	pipe_cmd = parser("echo \\\\\\\\;");
	// for (int k = 0; myenv[k] ; k++)
	// 	printf("%s\n", myenv[k]);
	free_pipe_cmd(pipe_cmd);
}