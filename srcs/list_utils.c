#include "./../includes/minishell.h"

void	lstadd_value(t_list **list, void *value)
{
	t_list *new = malloc(sizeof(new));
	t_list *last;

	new->content = value;
	new->next = NULL;

	if (!(*list))
		*list = new;
	else
	{
		last = ft_lstlast(*list);
		last->next = new;
	}
}