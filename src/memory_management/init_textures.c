#include "../../Include/doom_nukem.h"
#include "../../Include/map_struct.h"

/*
**		works with *.bmp format; need for more (watch in subject)
*/

t_texture			*init_single_texture(char *name, t_data *data)
{
	SDL_Surface		*loaded_image;
	t_texture		*init;
	uint32_t		*pixels;

	loaded_image = safe_call_ptr(SDL_LoadBMP(name),
							"Can\'t initialize texture.", data);
	pixels = (uint32_t *)safe_call_ptr(malloc(sizeof(char)
							* loaded_image->h * loaded_image->pitch),
						"malloc crashed, watch out!", data);
	init = (t_texture *)safe_call_ptr(ft_memalloc(sizeof(t_texture)),
					"malloc crashed, watch out!", data);
	ft_memcpy(pixels, loaded_image->pixels,
				loaded_image->h * loaded_image->pitch);
	init->bit_map = pixels;
	init->width = loaded_image->w;
	init->height = loaded_image->h;
	init->text_name = safe_call_ptr(ft_strdup(ft_strrchr(name, '/') + 1),
								 "Malloc was crashed. Function init_texture, "
		 						"main module, file init_single_textures.", data);
	SDL_FreeSurface(loaded_image);
	return (init);
}

/*
**		there are 3 textures for now; I guess
**		later there will be a pool of hardcoded textures;
**		mb one day we will write some functions to load new
**		textures and, mb, it would be easy to make hash-table
**		before parsing
*/

static t_texture	**init_textures_main(char *textures_path,
								int how_much, t_data *data)
{
	t_texture	**res;
	int			i;
	char		*name;
	int			flag;
	int			fd;

	i = 0;
	fd = open_file(textures_path, data);
	res = (t_texture **)safe_call_ptr(ft_memalloc(sizeof(t_texture *) *
		(how_much + 1)), "Malloc was crashed in \"init_textures_main\".", data);
	while ((flag = get_next_line(fd, &name)) == 1)
	{
		if (ft_strlen(name) > 1)
			res[i] = init_single_texture(name, data);
		ft_strdel(&name);
		i++;
	}
	ft_strdel(&name);
	safe_call_int(flag, "Can't read file."
					"Crashed in function: \"init_textures_main\".", data);
	safe_call_int(close(fd), "Can\'t close file."
		"Function init_textures, main module, file init_textures.", data);
	return (res);
}

t_texture			**init_textures(char *path, t_data *data)
{
	int		fd;
	int		flag;
	char	*line;
	int		how_much;

	how_much = 0;
	fd = open_file(path, data);
	while ((flag = get_next_line(fd, &line)) == 1)
	{
		if (ft_strlen(line) > 1)
			how_much++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	safe_call_int(flag, "Can't read file."
			"Crashed in function: \"init_textures\".", data);
	safe_call_int(close(fd), "Can\'t close file."
			"Function init_textures, main module, file init_textures.", data);
	return (init_textures_main(path, how_much, data));
}

void				remove_textures(t_data *data)
{
	int			i;

	i = 0;
	if (!data || !data->textures)
		return ;
	while (data->textures[i])
	{
		ft_strdel(&data->textures[i]->text_name);
		ft_memdel((void **)&data->textures[i]);
		i++;
	}
	ft_memdel((void **)&data->textures);
}

t_texture		*find_texture_by_name(char *name, t_data *data)
{
	int			i;

	i = 0;
	while (data->textures[i])
	{
		if (ft_strstr(data->textures[i]->text_name, name))
			return (data->textures[i]);
		i++;
	}
	safe_call_int(-1, "Didn't find right texture. Check "
				   "if maps are right.", data);
	return NULL;
}
