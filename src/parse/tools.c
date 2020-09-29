//
// Created by Hugor Chau on 9/21/20.
//

#include "../../Include/map_struct.h"

char		*skip_to(char *check, char *original)
{
	while (*original && (*original == ' ' || *original == '\t' || *original == '\r'))
		original++;
	while (*check && *original)
	{
		if (*original != *check)
			return (NULL);
		check++;
		original++;
	}
	if (*check)
		return (NULL);
	while (*original && (*original == ' ' || *original == '\t' || *original == '\r'))
		original++;
	return (original);
}

/*
**		TODO: check the fucking result!
*/

int			parse_num(char *str, uint32_t *box)
{
	uint32_t		res;

	res = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			res = res * 16 + *str - '0';
		else if (*str >= 'A' && *str <= 'F')
			res = res * 16 + *str - 'A' + 10;
		else if (*str >= 'a' && *str <= 'f')
			res = res * 16 + *str - 'a' + 10;
		else
			return (-1);
		str++;
	}
	*box = res;
	ft_putnbr(res);
	ft_putendl("");
	return (0);
}

//TODO: not a trustable function, segfault if there are not integers

char		*parse_float(char *str, float *box)
{
	float	res;
	int		i;
	char	flag;
	char	sign;
//	char	box;

	i = 0;
	sign = 1;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r'))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return (NULL);
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')))
		i++;
	if (str[i] != '.' && str[i] != ',')
		return (NULL);
	str[i] = '\0';
	*box = ft_atoi(str);
	str += i + 1;
	if (*str < '0' || *str > '9')
		return (NULL);
	i = 0;
	while (str[i] && ((str[i] >= '0' && str[i] <= '9')))
		i++;
	flag = str[i] == '\0' ? 0 : 1;
	str[i] = '\0';
	res = ft_atoi(str);
	while (res > 1)
		res /= 10.0;
	*box += res;
	str += i + flag;
	*box *= sign;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r'))
		str++;
	return (str);
}

/*
**		this function checks if word or line were correct
*/

int				check_line(char *should_be, char *check)
{
	if (!check || !should_be || !*check)
		return (1);
	while (*check && (*check == ' ' || *check == '\t' || *check == '\r'))
		check++;
	if (!*check)
		return (1);
	while (*should_be && *check && *should_be == *check)
	{
		check++;
		should_be++;
	}
	while (*check && (*check == ' ' || *check == '\t' || *check == '\r'))
		check++;
	return (*should_be == '\0' ? 0 : 1);
}

/*
**		local check at when one object was parsed
*/

void		check_error(t_parse **parse, char brackets, t_data *data)
{
	if ((*parse)->gnl_read_flag == -1)
		safe_call_parse_int(-1, "Read error: gnl returned -1.", data, parse);
	safe_call_parse_int(brackets, "Parse error: "
								  "check for brackets.", data, parse);
}
