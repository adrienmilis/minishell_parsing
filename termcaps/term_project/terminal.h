#ifndef TERM_H
# define TERM_H

# include <stdlib.h>
# include <unistd.h>
# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <termios.h>

typedef struct s_command
{
	char				*command;
	struct s_command	*prev;
	struct s_command	*next;
}				t_command;

int	ft_strlen(char *str);

// t_command	ft_lstaddnew(t_command *begin_list, char *str);
int			list_len(t_command *begin_list);
void		print_lst_elem(t_command *begin_list, int index);
// void		print_list(t_command *begin_list);

t_command	*new_elem(char *str, t_command *begin_list);
void		ft_lstadd_front(t_command **begin_list, t_command *new_elem);
void		add_elems(t_command **begin_list);
void		print_list(t_command *begin_list);
void		free_list(t_command	*begin_list);

char		*ft_strdup(char *str);
int 		init_termcap();
int			ft_strlen(char *str);
char		*make_buffer(char *buf, char c);
void		print_buffer(char *buf);
void		updown_event(int reset, char rd[3], t_command *begin_list);
int			read_input(char **buf, t_command **begin_list);
void		exit_free(char *str, t_command *begin_list, char *buffer);

#endif
