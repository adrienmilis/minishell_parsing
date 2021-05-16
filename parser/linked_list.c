#include "parser.h"

t_pipe_cmd	*ft_lstlast(t_pipe_cmd *begin_list)
{
	t_pipe_cmd	*elem;

	if (begin_list == NULL)
		return (begin_list);
	elem = begin_list;
	while (elem->next != NULL)
		elem = elem->next;
	return (elem);
}

void	ft_lstadd_back(t_pipe_cmd **begin_list, t_pipe_cmd *new_elem)
{
	t_pipe_cmd	*last_elem;

	if (!(*begin_list))
	{
		*begin_list = new_elem;
		return ;
	}
	last_elem = ft_lstlast(*begin_list);
	last_elem->next = new_elem;
}

t_pipe_cmd	*new_elem()
{
	t_pipe_cmd	*elem;

	elem = malloc(sizeof(t_pipe_cmd));
	if (elem == NULL)
		return (NULL);
	elem->cmd = NULL;
	elem->input = NULL;
	elem ->output = NULL;
	elem->double_greater = 0;
	elem->next = NULL;
	return (elem);
}

void	print_list(t_pipe_cmd *begin_list)
{
	t_pipe_cmd	*elem;
	int			i;

	elem = begin_list;
	while (elem)
	{
		i = 0;
		if (elem->cmd)
		{
			while (elem->cmd[i])
			{	
				printf("[%d] : [%s]\n", i, elem->cmd[i]);
				i++;
			}
		}
		printf("input : [%s]\n", elem->input);
		printf("output : [%s]\n", elem->output);
		printf(">> : %d\n", elem->double_greater);
		printf("----------\n");
		elem = elem->next;
	}
}

// int main()
// {
// 	char **args;

// 	args = malloc(sizeof(char *) * 4);
// 	args[3] = 0;
// 	args[0] = "echo";
// 	args[1] = "-n";
// 	args[2] = "bonjour";
// 	int i = -1;
// 	/*while (args[++i])
// 	{
// 		printf("%s\n", args[i]);
// 	}*/
	
// 	t_pipe_cmd *begin_list;
// 	t_pipe_cmd *elem;

// 	begin_list = NULL;
// 	ft_lstadd_back(&begin_list, new_elem());
// 	// begin_list->cmd = malloc(sizeof(char *) * 4);
// 	// begin_list->cmd[3] = 0;
// 	// begin_list->cmd[0] = "echo";
// 	// begin_list->cmd[1] = "-n";
// 	// begin_list->cmd[2] = "bonjour";
// 	begin_list->cmd = args;
// 	elem = new_elem();
// 	ft_lstadd_back(&begin_list, elem);
// 	elem->cmd = args;
// 	elem = new_elem();
// 	ft_lstadd_back(&begin_list, elem);
// 	elem->cmd = args;
// 	elem->cmd[0] = "cd";
// 	print_list(begin_list);
// 	return (0);
// }