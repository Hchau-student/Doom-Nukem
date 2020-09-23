#include "../libft/libft.h"
#include "../Include/doom_nukem.h"
#define ERROR			"\033[38;2;200;0;30m"
#define EOC				"\033[38;2;0m"

int		safe_call_int(int res, char *message, t_data *data)
{
	if (res == 0)
		return (res);
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(EOC, 2);
	remove_data(data);
	exit(0);
}

void	*safe_call_ptr(void *res, char *message, t_data *data)
{
	if (res != NULL)
		return (res);
	ft_putstr_fd(ERROR, 2);
	ft_putendl_fd(message, 2);
	ft_putstr_fd(EOC, 2);
	remove_data(data);
	exit(0);
}
