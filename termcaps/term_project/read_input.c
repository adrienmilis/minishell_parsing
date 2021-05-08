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

void	print_buffer(char *buf)
{
	//printf("%s\n", buf);
	printf("\n");
}

void	updown_event(char rd[3], t_command *begin_list)
{
	// static int	up = -1;
	int					ls_len;
	static t_command	*elem = NULL;


	ls_len = list_len(begin_list);
	if (rd[2] == 65) // up arrow
	{
		if (elem == NULL)
			elem = begin_list;
		else
			elem = elem->next;
		printf("%s\n", begin_list->command);
		// if (up < ls_len - 1)
		// 	up++;
		// print_lst_elem(*begin_list, up);
	}
	if (rd[2] == 66) // down arrow
	{
		if (elem == NULL)
			printf("\n");
		//printf("%s\n", begin_list->command);
		// if (up >= 0)
		// 	up--;
		// print_lst_elem(*begin_list, up);
	}
}

int	read_input(char **buf, t_command **begin_list)
{
	char		rd[4];
	int			ret;
	char		*new_buf;

	ret = read(0, &rd, 4);
	if (ret == -1)
		return (ret);
	if (isprint(rd[0]))
	{
		*buf = make_buffer(*buf, rd[0]);
		write(1, &rd[0], 1);
	}
	else if (rd[0] == '\033')
		updown_event(rd, *begin_list);
	else if (rd[0] == 10)
	{
		print_buffer(*buf);			// execute the command (here, print a NL)
		//new_buf = ft_strdup(*buf);
		//printf("buf : %s\n", *buf);
		ft_lstadd_front(begin_list, new_elem(*buf));			// adds the new command to the list
		print_list(*begin_list);
		free(*buf);
		*buf = NULL;
	}
	return (ret);
}
