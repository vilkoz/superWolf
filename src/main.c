/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:26:41 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 23:22:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"
#include "configs.h"
#include "drawer.h"

void	init_sdl(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		perror(SDL_GetError());
		exit(1);
	}
	if ((sdl->win = SDL_CreateWindow("wolf == duke", 0, 0, W, H, 0)) == NULL)
	{
		perror(SDL_GetError());
		exit(1);
	}
	sdl->surface = SDL_GetWindowSurface(sdl->win);
	sdl->quit = 0;
	sdl->player = player();
	SDL_CreateWindowAndRenderer(640, 480, 0, &sdl->win2, &sdl->r);
}

void	close_sdl(t_sdl *sdl)
{
	SDL_FreeSurface(sdl->surface);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	handle_events(t_sdl *s)
{
	SDL_Event		e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			s->quit = 1;
		else if (e.type == SDL_KEYDOWN)
		{
			(e.key.keysym.sym == SDLK_w) ? player_move(&s->player, 1) : 0;
			(e.key.keysym.sym == SDLK_s) ? player_move(&s->player, -1) : 0;
			(e.key.keysym.sym == SDLK_a) ? player_rotate(&s->player, -5.0/90.0) : 0;
			(e.key.keysym.sym == SDLK_d) ? player_rotate(&s->player, 5.0/90.0) : 0;
			(e.key.keysym.sym == SDLK_w) ? player_move(&s->player, 1) : 0;
		}
	}
}

int		main(void)
{
	t_sdl		s;

	init_sdl(&s);
	s.sectors = parse("map.txt");
	while (!s.quit)
	{
		SDL_FillRect(s.surface, NULL, 0);
		draw_sectors(&s, s.sectors, s.player);
		handle_events(&s);
		SDL_UpdateWindowSurface(s.win);
		SDL_Delay(100);
	}
	close_sdl(&s);
	return (0);
}
