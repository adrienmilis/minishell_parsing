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

void	exit_free(char *str, t_command *begin_list, char *buffer)
{
	if (buffer)
		free(buffer);
	if (begin_list)
		free_list(begin_list);
	printf("Error : %s\n", str);
	exit(0);
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
			exit_free("Termios error", *begin_list, NULL);
		if (tcgetattr(0, &s_termios_backup) == -1)
			exit_free("Termios error", *begin_list, NULL);
		s_termios.c_lflag &= ~(ICANON);
		s_termios.c_lflag &= ~(ECHO);
		if (tcsetattr(0, 0, &s_termios) == -1)
			exit_free("Termios error", *begin_list, NULL);
		while (ret >= 0)
			ret = read_input(&buf, begin_list);
		if (tcsetattr(0, 0, &s_termios_backup) == -1)
			exit_free("Termios error", *begin_list, NULL);
	}
	return (0);
}

int	main(void)
{
	char		*buf;
	t_command	*begin_list;
	int			ret;

	begin_list = malloc(sizeof(t_command));
	if (begin_list == NULL)
		exit_free("Malloc error", NULL, NULL);
	begin_list->next = NULL;
	begin_list->prev = NULL;
	begin_list->command = NULL;
	buf = NULL;
	main_2(buf, &begin_list);
	free_list(begin_list);
	return (0);
}
