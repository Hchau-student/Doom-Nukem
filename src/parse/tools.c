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

char		*parse_float(char *str, float *box)
{
	while (*str && ((*str >= '0' && *str <= '9') || (*str == '.' || *str == ',')))
		str++;
	while (*str && (*str == ' ' || *str == '\t' || *str == '\r'))
		str++;
//	while (*str)
//	{
//
//	}
	return (str);
}

/*
**		this function checks if word or line were correct
*/

int				check_line(char *should_be, char *check)
{
	if (!check || !should_be)
		return (1);
	while (*check && (*check == ' ' || *check == '\t' || *check == '\r'))
		check++;
	while (*should_be && *check && *should_be == *check)
	{
		check++;
		should_be++;
	}
	while (*check && (*check == ' ' || *check == '\t' || *check == '\r'))
		check++;
	return (*should_be == '\0' ? 0 : 1);
}
