#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

/*
**		the whole file is just sdl-initialization, you can skip it,
**		I guess it shouldn't be any troubles in here
*/

static void		init_rect(t_data *data)
{
	SDL_Rect *background_rect;

	background_rect = safe_call_ptr((SDL_Rect *)malloc(sizeof(SDL_Rect)),
							"Crashed malloc at making rect!", data);
	background_rect->x = 0;
	background_rect->y = 0;
	background_rect->w = SCREEN_WIDTH;
	background_rect->h = SCREEN_HEIGHT;
	data->sdl->rect = background_rect;
}

static void		init_text(t_data *data)
{
	uint32_t	*pixels;

	data->sdl->tex = safe_call_ptr(SDL_CreateTexture(data->sdl->rend,
							SDL_PIXELFORMAT_ARGB8888,
							SDL_TEXTUREACCESS_STREAMING,
							SCREEN_WIDTH, SCREEN_HEIGHT),
							"SDL-texture init failed.", data);
	pixels = (uint32_t *)safe_call_ptr(malloc(((SCREEN_HEIGHT) *
							(SCREEN_WIDTH)) * sizeof(uint32_t)),
								"Crashed malloc at making bitmap!", data);
	data->sdl->color_buffer = pixels;
	safe_call_int(SDL_SetRenderDrawColor(data->sdl->rend, 0, 0, 0, SDL_ALPHA_OPAQUE),
						"Can't clear render.", data);
	safe_call_int(SDL_RenderClear(data->sdl->rend), "Can't clear render.", data);
	safe_call_int(SDL_RenderCopy(data->sdl->rend, data->sdl->tex, NULL, NULL),
			"Can't clear render.", data);
	SDL_RenderPresent(data->sdl->rend);
}

void			init_sdl(t_data *data, char *name)
{
	data->sdl->win = NULL;
	safe_call_int((SDL_Init(SDL_INIT_EVERYTHING)), "SDL init failed.", data);
	data->sdl->win = safe_call_ptr((SDL_CreateWindow(name, SCREEN_WIDTH, 200,
								SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)),
						"SDL-window init failed.", data);
	data->sdl->rend = safe_call_ptr(
			SDL_CreateRenderer(data->sdl->win, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
			"SDL-renderer init failed.", data);
	init_rect(data);
	init_text(data);
	return ;
}

void			remove_sdl(t_sdl **remove)
{
	if (remove == NULL || *remove == NULL)
		return ;
	if ((*remove)->rect != NULL)
		ft_memdel((void **)&(*remove)->rect);
	if ((*remove)->color_buffer != NULL)
		ft_memdel((void **)&(*remove)->color_buffer);
	if ((*remove)->win != NULL)
		SDL_DestroyWindow((*remove)->win);
	SDL_Quit();
	ft_memdel((void **)remove);
}
