#include "terminal.h"
#include <ctype.h>

int init_termcap()
{
	int		ret;
	char	*term_type;

	term_type = getenv("TERM");
	if (term_type == NULL)
		return (-1);
	ret = tgetent(NULL, term_type);
	if (ret == 0 || ret == -1)
		return (-1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*make_buffer(char *buf, char c)
{
	char	*buf_cpy;
	int		buf_len;
	int		i;

	i = 0;
	buf_len = ft_strlen(buf);
	buf_cpy = malloc((buf_len + 2) * sizeof(char));
	if (buf_cpy == NULL)
		return (NULL);
	while (i < buf_len)
	{
		buf_cpy[i] = buf[i];
		i++;
	}
	buf_cpy[i] = c;
	buf_cpy[i + 1] = '\0';
	free(buf);
	return (buf_cpy);
}

void	print_nl(char *buf)
{
	printf("\n");
}

void	updown_event(int reset, char rd[3], t_command *begin_list)
{
	static t_command	*elem;

	if (reset == 1)
		elem = NULL;
	if (begin_list->next == NULL)
		return ;
	if (rd[2] == 65) // up arrow
	{
		if (elem == NULL)
			elem = begin_list;
		else if (elem->next != NULL)
			elem = elem->next;
		if (elem->command)
			printf("%s\n", elem->command);
	}
	if (rd[2] == 66) // down arrow
	{
		if (elem == NULL || elem == begin_list)
			elem = NULL;
		else
			elem = elem->prev;
		if (elem)
			printf("%s\n", elem->command);
	}
}

/* OPTIONNEL :
implémenter l'element temporaire :
- quand tu ecris qqchose et puis que tu remontes dans l'historique, ca ajoute ce que tu as ecrit
a l'historique
- si lorsque tu remontes dans l'historique, tu executes une commande de l'historique
(tu appuyes sur entree), alors c'est cette commande qui est ajoutee a l'historique a la place */

int	enter_input(t_command **begin_list, char **buf)
{
	print_nl(*buf);										// execute the command (here, print a NL)
	ft_lstadd_front(begin_list, new_elem(*buf, *begin_list));		// adds the new command to the list
	free(*buf);
	*buf = NULL;
	return (1);		// reset is set to 1 so the history starts at the first command again
}

int	read_input(char **buf, t_command **begin_list)
{
	char		rd[4];
	int			ret;
	char		*new_buf;
	static int	reset;

	ret = read(0, &rd, 4);
	if (ret == -1)
		exit_free("Read error", *begin_list, NULL);
	if (isprint(rd[0]))
	{
		*buf = make_buffer(*buf, rd[0]);
		if (*buf == NULL)
			exit_free("Malloc error", *begin_list, NULL);
		write(1, &rd[0], 1);
	}
	else if (rd[0] == '\033')
	{
		updown_event(reset, rd, *begin_list);
		reset = 0;
	}
	else if (rd[0] == 10)	// if enter is pressed
		reset = enter_input(begin_list, buf);
	return (ret);
}
