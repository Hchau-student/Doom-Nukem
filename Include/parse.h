//
// Created by Hugor Chau on 9/16/20.
//


#ifndef DOOM_NUKEM_PARSE_H
#define DOOM_NUKEM_PARSE_H
# include <stdint.h>
#include "../libft/libft.h"

struct s_sector;
struct s_data;

/*
**		we don't actually know, how much of everything do we have
**		while we parse, so lists indeed!
*/

/*
**		это для утечек
*/

typedef struct		s_parse
{
	t_list			*gnl_str;
	char			gnl_read_flag;
	char			brackets;
	char			player_parsed;
	char			player_hud_parsed;
	uint32_t		sector_count;
	t_list			*check_portals;//будет быстрее всё
	// сюда сразу распихать лол, чтобы не проходить
	// тысячу раз по сектору
	char			*cur_str;
	struct s_sector	*cur_sector;
	int64_t			fd;
	int64_t			sector_index;
	char			*error_message;
}					t_parse;

/*
**		parse
*/

void			parse(char *str, struct s_data *data);
void			parse_wall(t_parse **parse, struct s_data *data);
void			parse_sector(t_parse **parse, struct s_data *data);
void			parse_line_sector(t_parse **parse, struct s_data *data);
void			parse_objects(t_parse **parse, struct s_data *data);
void			*parse_object(t_parse **parse, struct s_data *data);
t_twlist		*parse_single_wall(t_parse **parse, struct s_data *data);
void			parse_player(t_parse **parse, struct s_data *data);
void			parse_hud(t_parse **parse, struct s_data *data);
void			parse_player_line(t_parse **parse, struct s_data *data);

/*
**		check data
*/

void		check_walls_data(struct s_sector *sector, struct s_data *data);

//проверить, не пересекают ли стены друг друга
void		check_sector_data(struct s_sector *sector, struct s_data *data);
void		check_objects_data(struct s_sector *sector, struct s_data *data);
//проверить, все ли объекты находятся в обозначенных секторах,
//переназначить сектора, если нужно

/*
**		parse tools
*/

char			*skip_to(char *check, char *original);
int				parse_num(char *str, uint32_t *box);
char			*parse_float(char *str, float *box);
int				check_line(char *should_be, char *check);

int		safe_call_parse_int(int res, char *message,
							struct s_data *data, t_parse **parse);
void	*safe_call_parse_ptr(void *res, char *message,
							struct s_data *data, t_parse **parse);
void		remove_parse(t_parse **parse);

#endif
