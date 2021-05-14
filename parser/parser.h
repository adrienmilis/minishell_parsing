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

typedef struct s_pars
{
	int in_s_quotes;
	int	in_d_quotes;
	int	semicolon;
}				t_pars;

// ft_split.c
char	**ft_split(const char *str, char c);

// errors.c
void	error_exit(char *msg);

// parser.c
int			append_arg(char **args, char *word);
t_pipe_cmd	*parser(char *cmd);

// utils.c
int		semicolons_valid(char *cmd);
int		quotes_are_closed(char *cmd);
int		is_space(char c);
void 	set_quotes(int i, char *cmd, t_pars *p);
void	init_pars_struct(t_pars *p);
int		pipes_valid(char *cmd);
void	check_syntax(char *cmd);
int		is_reserved_word(char c);

// linked_list.c

t_pipe_cmd	*ft_lstlast(t_pipe_cmd *begin_list);
void		ft_lstadd_back(t_pipe_cmd **begin_list, t_pipe_cmd *new_elem);
t_pipe_cmd	*new_elem();
void		print_list(t_pipe_cmd *begin_list);

// libft.c

int		ft_strlen(char *str);

#endif