#include "terminal.h"

int	list_len(t_command *begin_list)
{
	// renvoie le nb d'elements non nuls dans la liste
	t_command	*elem;
	int			i;

	elem = begin_list->next;
	i = 0;
	while (elem)
	{
		elem = elem->next;
		i++;
	}
	return (i);
}

t_command	*new_elem(char *str)
{
	t_command	*new_elem;
	char		*command;

	new_elem = malloc(sizeof(t_command));
	if (!new_elem)
		return (NULL);
	command = ft_strdup(str); // proteger !!!
	new_elem->next = NULL;
	new_elem->prev = NULL;
	new_elem->command = command;
	return (new_elem);
}

void	ft_lstadd_front(t_command **begin_list, t_command *new_elem)
{
	t_command	*bg_list;

	new_elem->next = *begin_list;	// faire pointer le nv premier vers le 2e
	bg_list = *begin_list;
	bg_list->prev = new_elem;		// le 2e pointe vers le premier
	*begin_list = new_elem;			// faire en sorte que le nvl elem soit le nv premier
	//print_list(*begin_list);
}

void	add_elems(t_command **begin_list)
{
	ft_lstadd_front(begin_list, new_elem("ls -la"));
	ft_lstadd_front(begin_list, new_elem("grep kikoo"));
	ft_lstadd_front(begin_list, new_elem("ping tralala"));
	ft_lstadd_front(begin_list, new_elem("kiakikodu"));
	ft_lstadd_front(begin_list, new_elem("saluuuut"));
}

void	print_list(t_command *begin_list)
{
	t_command	*elem;
	int			i;

	i = 0;
	elem = begin_list;
	while (elem->next)
	{
		printf("[%d] : %s\n", i, elem->command);
		elem = elem->next;
		i++;
	}
}

void	free_list(t_command	*begin_list)
{
	// bien proteger !!
	// checker si on doit free la string a linterieur si on la malloc mais il y a bien moyen !!!!!!!!
	t_command	*prev;
	t_command	*current;

	prev = begin_list;
	current = prev->next;
	while (prev->next)
	{
		free(prev);
		prev = current;
		if (current->next)
			current = current->next;
	}

}

void	print_lst_elem(t_command *begin_list, int index)
{
	t_command	*elem;
	int	i;

	if (index == -1) // on a une ligne vide quand l'index est à -1
		printf("\n");
	if (begin_list->next == NULL)
		return ;
	elem = begin_list->next;
	i = 0;
	while (i < index && elem != NULL)
	{
		elem = elem->next;
		i++;
	}
	printf("%s\n", elem->command);	
}

// int main()
// {
// 	t_command	*begin_list;
// 	char		*buf;
// 	char		*str;

// 	buf[0] = 0;
// 	begin_list->next = NULL;
// 	begin_list->prev = NULL;
// 	begin_list->command = NULL;

// 	int i = 0;

// 	// add_elems(&begin_list);
// 	// add_elems(&begin_list);
// 	while (i < 5)
// 	{
// 		buf = malloc(2);
// 		read(0, &buf[0], 2);
// 		buf[1] = '\0';
// 		ft_lstadd_front(&begin_list, new_elem(buf));
// 		print_list(begin_list);
// 		i++;
// 	}
// 	print_list(begin_list);
// 	free_list(begin_list);
// 	return (0);
// }