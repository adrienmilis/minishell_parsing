#include "parser.h"

int main(int argc, char **argv)
{
	t_pipe_cmd	*pipe_cmd;

	pipe_cmd = parser("< test < allo > kikoo >> salut > mais bonjour echo salut  < salut   |t a  d z < echo > salut | allo test cv | cmt hello");
	free_pipe_cmd(pipe_cmd);
}