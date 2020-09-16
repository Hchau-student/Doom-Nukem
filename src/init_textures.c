#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

/*
**		works with *.bmp format; need for more (watch in subject)
*/

static t_texture	*init_texture(char *name, t_data *data)
{
	SDL_Surface		*loaded_image;
	t_texture		*init;
	uint32_t		*pixels;

	loaded_image = safe_call_ptr(SDL_LoadBMP(name),
							"Can not initialize texture.", data);
	pixels = safe_call_ptr(malloc(sizeof(uint32_t)
							* loaded_image->h * loaded_image->pitch),
						"malloc crashed, watch out!", data);
	init = safe_call_ptr(malloc(sizeof(t_texture *)),
					"malloc crashed, watch out!", data);
	ft_memcpy(pixels, loaded_image->pixels,
				loaded_image->h * loaded_image->pitch);
	init->bit_map = pixels;
	init->width = loaded_image->w;
	init->height = loaded_image->h;
	return (init);
}

/*
**		there are 3 textures for now; I guess
**		later there will be a pool of hardcoded textures;
**		mb one day we will write some functions to load new
**		textures and, mb, it would be easy to make hash-table
**		before parsing
*/

t_texture			**init_textures_main(char **textures_data, int how_much, t_data *data)
{
	t_texture	**res;
	int			i;

	i = 0;
	res = (t_texture **)safe_call_ptr(malloc(sizeof(t_texture *) * (how_much + 1)),
								   "Malloc was crashed in \"init_textures_main\".", data);
	while (i < how_much)
	{
		res[i] = init_texture(textures_data[i], data);
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_texture			**init_textures(char **textures_data, int how_much, t_data *data)
{
	char	*textures[3];

	textures[0] = "./extra_src/12.bmp";
	textures[1] = "./extra_src/9.bmp";
	textures[2] = "./extra_src/14.bmp";
	how_much = 3;
	if (textures_data != NULL)
		;
	return (init_textures_main(textures, how_much, data));
}

void				remove_textures(t_data *data)
{
	int			i;

	i = 0;
	if (!data || !data->textures)
		return ;
	while (data->textures[i])
	{
		ft_memdel((void **)&data->textures[i]);
		i++;
	}
	ft_memdel((void **)&data->textures);
}
