#include "parser.h"

int main(int argc, char **argv, char **env)
{
	t_pipe_cmd	*pipe_cmd;

	(void)argc;
	(void)argv;
	myenv = new_env(env);
	pipe_cmd = parser("echo bonjour >salut", 1);
	/*for (int k = 0; myenv[k] ; k++)
		printf("%s\n", myenv[k]);*/
	free_pipe_cmd(pipe_cmd);
}
