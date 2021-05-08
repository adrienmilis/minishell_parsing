#include "terminal.h"

char	*ft_strdup(char *str)
{
	char	*str_cpy;
	int		str_len;
	int		i;

	i = 0;
	str_len = ft_strlen(str);
	str_cpy = malloc((str_len + 1) * sizeof(char));
	if (str_cpy == NULL)
		return (NULL);
	while (i < str_len)
	{
		str_cpy[i] = str[i];
		i++;
	}
	str_cpy[i] = '\0';
	return (str_cpy);
}


int	main_2(char *buf, t_command **begin_list)
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
			ret = read_input(&buf, begin_list);
		if (tcsetattr(0, 0, &s_termios_backup) == -1)
			return (-1);
	}
	return (0);
}

int main()
{
	char		*buf;
	t_command	*begin_list;

	// buf = malloc(sizeof(char) * 2048);
	// buf[0] = 0;
	begin_list = malloc(sizeof(t_command));
	begin_list->next = NULL;
	begin_list->prev = NULL;
	begin_list->command = NULL;
	buf = NULL;
	main_2(buf, &begin_list);
	return (0);
}

