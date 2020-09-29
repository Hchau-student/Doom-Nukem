#include "../../libft/libft.h"
#include "../../Include/doom_nukem.h"
#define ERROR			"\033[38;2;200;0;30m"
#define EOC				"\033[38;2;0m"

void		remove_parse(t_parse **parse)
{
	t_list	*lst;
	t_list	*tmp;

	lst = (*parse)->gnl_str;
	while (lst)
	{
		tmp = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void **)&lst);
		lst = tmp;
	}
	lst = (*parse)->check_portals;
	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&lst);
		lst = tmp;
	}
	ft_memdel((void **)parse);
}

int		safe_call_parse_int(int res, char *message,
							t_data *data, t_parse **parse)
{
	if (res == 0)
		return (res);
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(EOC, 2);
	remove_data(data);
	remove_parse(parse);
	exit(0);
}

void	*safe_call_parse_ptr(void *res, char *message,
							t_data *data, t_parse **parse)
{
	if (res != NULL)
		return (res);
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(EOC, 2);
	remove_data(data);
	remove_parse(parse);
	exit(0);
}
