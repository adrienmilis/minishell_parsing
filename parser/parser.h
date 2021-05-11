#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_pipe_cmd
{
	char				**cmd;
	char				*input;
	char				*output;
	int					double_greater;		// booleen pour >>
	struct s_pipe_cmd	*next;
}				t_pipe_cmd;

typedef struct s_command
{
	t_pipe_cmd			*pipe_cmd_start;	// début de la liste chainee de pipe cmds
	struct s_command	*next;
}				t_command;

// ft_split.c
char	**ft_split(const char *str, char c);

// parser.c
int		is_valid_input(char *cmd);

#endif