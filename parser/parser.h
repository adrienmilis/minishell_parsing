#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

char	**myenv;

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
	int	i;
}				t_pars;

// ft_split.c
char	**ft_split(const char *str, char c);

// errors.c
void	free_pipe_elems(t_pipe_cmd *c);
void	free_pipe_cmd(t_pipe_cmd *begin_list);
void	error_exit(char *msg, t_pipe_cmd *begin_list);

// parse_out_quotes.c
void	real_sign2(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd, char sign);
void	real_sign(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd);
void	reserved_chars(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd);
void	parse_out_quotes(t_pars *p, t_pipe_cmd *p_cmd_start, char *cmd);

// parser.c
t_pipe_cmd	*parser(char *cmd);

// add_arguments.c
void		add_argument(t_pipe_cmd *last, t_pipe_cmd *p_cmd_start, t_pars *p, char *cmd);
char		*get_next_word(char *cmd, t_pars *p, t_pipe_cmd *p_cmd_start);
char		*copy_next_word(char *cmd, t_pars *p, int word_size, t_pipe_cmd *p_cmd_start);
int			append_arg(t_pipe_cmd *lasts, char *word);

// utils.c
t_pipe_cmd	*init_pipe_list();
void		init_pars_struct(t_pars *p);
void		reset_pars_struct(t_pars *p);

// check_syntax.c
int		semicolons_valid(char *cmd);
int		quotes_are_closed(char *cmd);
void 	set_quotes(int i, char *cmd, t_pars *p);
int		pipes_valid(char *cmd);
void	check_syntax(char *cmd);

// check_chars.c
int		is_space(char c);
int		is_r_space(char *c, int i);
int		is_reserved_char(char c, int dollar);
int		is_r_resvd_char(char *c, int i, int dollar);
int		is_quote(char c);
int		is_r_quote(char *c, int i);
int		is_unesc_char(char *c, int i);

// linked_list.c
t_pipe_cmd	*ft_lstlast(t_pipe_cmd *begin_list);
void		ft_lstadd_back(t_pipe_cmd **begin_list, t_pipe_cmd *new_elem);
t_pipe_cmd	*new_elem();
void		print_list(t_pipe_cmd *begin_list);

// libft.c
char	*ft_strdup_len(char *str, int len);
char	*ft_strdup(char *str);
int		ft_strlen(char *str);
int		is_number(char c);
int		is_letter(char c);
int		valid_var_char(char c);

// env.c 
int		strcmp_env(char *s1, char *s2);
char	**new_env(char **env);

// env_vars.c
char 	*unvalid_var_name(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start);
char	*get_env_var(int index);
char	*valid_var_name(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start);
char	*get_variable(t_pars *p, char *cmd, t_pipe_cmd *p_cmd_start);

#endif