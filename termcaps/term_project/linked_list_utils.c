#include "terminal.h"

// changer begin_list en double pointeur et de sorte que ce soit le 1er elem de la liste ??
t_command	ft_lstaddnew(t_command *begin_list, char *str)
{
	t_command	new_elem;

	new_elem.command = str;
	if (begin_list->next)
		begin_list->next->prev = &new_elem;
	new_elem.next = begin_list->next;
	new_elem.prev = NULL;
	begin_list->next = &new_elem;
	return (new_elem);
}

t_command	ft_lstnew(t_command *begin_list, char *str)
{
	t_command	new_elem;

	new_elem.command = str;
	new_elem.next = NULL;
	new_elem.prev = NULL;
	return (new_elem);
}

void		ft_lstaddfront(t_command *begin_list, t_command *new_elem)
{
	if (begin_list->next)
	{
		*begin_list->next->prev = new_elem;
		new_elem->next = begin_list->next;
	}
	begin_list->next = new_elem;
}

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
	while (i < index && elem->next != NULL)
	{
		elem = elem->next;
		i++;
	}
	printf("%s\n", elem->command);	
}

void	print_list(t_command **begin_list)
{
	t_command	*elem;
	int			i;

	i = 0;
	elem = begin_list->next;
	while (elem)
	{
		printf("[c%d] : %s\n", i, elem->command);
		elem = elem->next;
		i++;
	}
}

void	add_new_elem(t_command **begin_list, char *str)
{
	ft_lstaddnew(begin_list, str);
}

//main to test adding new elements to the linked list

int main()
{
	t_command	*begin_list;
	t_command	elem;

	begin_list->next = NULL;
	begin_list->prev = NULL;
	begin_list->command = NULL;
	
	// ft_lstaddnew(&begin_list, "ls -la");
	// ft_lstaddnew(&begin_list, "grep niktamer");
	// ft_lstaddnew(&begin_list, "cd -i -dtc");
	// ft_lstaddnew(&begin_list, "allo le monde");
	
	// elem = ft_lstnew(&begin_list, "ls -la");
	// ft_lstaddfront(&begin_list, &elem);
	// elem = ft_lstnew(&begin_list, "grep niktamer");
	// ft_lstaddfront(&begin_list, &elem);
	// elem = ft_lstnew(&begin_list, "cd -i -dtc");
	// ft_lstaddfront(&begin_list, &elem);
	// elem = ft_lstnew(&begin_list, "allo le monde");
	// ft_lstaddfront(&begin_list, &elem);

	add_new_elem(&begin_list, "pipi");
	add_new_elem(&begin_list, "zizi");
	add_new_elem(&begin_list, "caca");
	add_new_elem(&begin_list, "prout");

	print_list(&begin_list);
	
	printf("list len : %d\n", list_len(&begin_list));
	//print_lst_elem(&begin_list, 0);
	return (0);
}