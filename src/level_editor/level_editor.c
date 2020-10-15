//
// Created by Hugor Chau on 10/7/20.
//

#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"
#include "../../Include/level_editor.h"
# include <dirent.h>

DIR			*open_directory(t_data *data)
{
	DIR			*dir_fd;

	if ((dir_fd = opendir("./parse_maps")) == NULL)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("./parse_maps", 2);
		ft_putstr_fd(":\n", 2);
		ft_putendl_fd(": Permission denied", 2);
		remove_data(data);
	}
	return (dir_fd);
}

void		change_map_name(t_data *data, char *new_name)
{
	ft_strdel(&data->menu.cur_map_name);
	data->menu.cur_map_name = new_name;
}

void		get_new_map_name(t_data *data)
{
	DIR						*dir_fd;
	struct dirent			*res;
	char					*full_name;
	int						max_name;
	char					*res_name;

	dir_fd = open_directory(data);
	res_name = NULL;
	max_name = 1;
	while ((res = readdir(dir_fd)))
	{
		if (res->d_name[0] == '.')
			continue ;
		if (max_name <= ft_atoi(res->d_name))
		{
			max_name = ft_atoi(res->d_name) + 1;
		}
	}
	res_name = ft_itoa(max_name);
	full_name = ft_strjoin(DEFAULT_PATH, res_name);
	change_map_name(data, full_name);
	ft_strdel(&res_name);
}

void		level_editor(t_data *data)
{
	init_level_editor(data);
	get_new_map_name(data);
	init_default_map(data);
	data->go_to->condition = &level_editor_condition;
}
