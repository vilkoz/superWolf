/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:29:03 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 18:35:45 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_H
# define SDL_H

# include <SDL2/SDL.h>
# include "player.h"
# include "sector.h"
# include "configs.h"
# include "../libft/include/libft.h"

# define MAX_QUEUE 32
# define INIT_ITEM(n, s, e) ((t_item){n, s, e})

typedef struct	s_item
{
	int			num;
	int			xstart;
	int			xend;
}				t_item;

typedef struct	s_sdl
{
	SDL_Window	*win;
	SDL_Surface	*surface;
	char		quit;
	t_sector	*sectors;
	t_player	player;
	int			ystart[W];
	int			yend[W];
	t_queue		queue;
// temporal
	SDL_Window	*win2;
	SDL_Renderer	*r;
}				t_sdl;

#endif
