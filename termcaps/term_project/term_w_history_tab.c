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
	printf("\n%s\n", buf);
}

char	**copy_tab(char **command_history, char **new_tab)
{
	int		i;
	int		j;

	i = 0;
	while (command_history[i])
	{
		new_tab[i] = malloc(sizeof(char) * (ft_strlen(command_history[i]) + 1));
		if (new_tab[i] == NULL)
			exit(-1);
		j = 0;
		while (command_history[i][j])
		{
			new_tab[i][j] = command_history[i][j];
			j++;
		}
		new_tab[i++][j] = 0;
	}
	new_tab[i] = 0;
	new_tab[i + 1] = 0;
	// free
	return (new_tab);
}


void	add_command_to_history(char **command_history, char *new_command)
{
	char	**new_tab;
	int		i;

	// !! ignorer la commande à rajouter si c'est une string vide
	if (new_command == NULL)
		return ;
	i = 0;
	while (command_history[i])
		i++;
	new_tab = malloc(sizeof(char *) * (i + 2));
	if (new_tab == NULL)
		exit(-1);


}

int	read_input(char **buf, char **command_history)
{
	char		rd[3];
	int			ret;
	
	ret = read(0, &rd, 3);
	if (ret == -1)
		return (ret);
	if (isprint(rd[0]))
	{
		*buf = make_buffer(*buf, rd[0]);
		write(1, &rd[0], 1);
	}
	else if (rd[0] == '\033')
	{
		if (rd[2] == 65)
			printf("UP ARROW\n");
		if (rd[2] == 66)
			printf("DOWN ARROW\n");
	}
	else if (rd[0] == 10)
	{
		// add command to history
		print_buffer(*buf); // execute the command (here, print the buffer)
		free(*buf);
		*buf = NULL;
	}
	return (ret);
}

int	main_2(char *buf, char **command_history)
{
	struct termios	s_termios;
	struct termios	s_termios_backup;
	int				ret;

	ret = 0;
	if (init_termcap() == 0)
	{
		if (tcgetattr(0, &s_termios) == -1)
			return (-1);
		if (tcgetattr(0, &s_termios_backup) == -1)
			return (-1);
		s_termios.c_lflag &= ~(ICANON);
		s_termios.c_lflag &= ~(ECHO);
		if (tcsetattr(0, 0, &s_termios) == -1)
			return (-1);
		while (ret >= 0)
			ret = read_input(&buf, command_history);
		if (tcsetattr(0, 0, &s_termios_backup) == -1)
			return (-1);
	}
	return (0);
}

int main()
{
	char	*buf;
	char	**command_history;

	buf = NULL;
	command_history = NULL;
	main_2(buf, command_history);
	return (0);
}

