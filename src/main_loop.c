//
// Created by Hugor Chau on 9/15/20.
//

#include "../Include/doom_nukem.h"
#include "../Include/map_struct.h"

void	main_loop(t_data *data)
{
	int quit = 0;
	SDL_Event event;
//	int is_pressed = FALSE;

//    int KEYS[322]; если нужно запомнить клаву, крутой пример
	while(!quit) {
		while (SDL_PollEvent(&event)) {
			//выведение битмапы
//			win->update_texture(win, draw);
//			win3d->update_texture(win3d, draw);

//			mouse_events(event, draw, &is_pressed);
//			SDL_PumpEvents(); // обработчик событий.
			if(event.type == SDL_QUIT)
				quit=1;
			if (quit == 1) {
//				SDL_DestroyWindow(data->sdl->win);
//				SDL_Quit();
//				exit(0);
				remove_data(data);
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = 1;
//				key_event(&event, draw);
			}
		}
	}
	remove_data(data);
}
