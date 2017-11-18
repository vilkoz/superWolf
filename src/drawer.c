/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 12:51:11 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 00:04:50 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"
#include "utility.h"
#include "vertex.h"
#include "player.h"
#include "configs.h"
#include "drawer.h"
#include <math.h>

void		draw_vline(t_sdl *s, t_vertex v1, t_vertex v2, unsigned color)
{
	SDL_Rect		rect;

	rect.x = (int)MIN(v1.x, v2.x);
	rect.y = (int)MIN(v1.y, v2.y);
	rect.w = 1;
	rect.h = (int)MAX(v2.y, v1.y) - rect.y;
	SDL_FillRect(s->surface, &rect, color);
}

void		draw_loop(t_sdl *s, t_vertex x, t_vertex vborder1, t_vertex vborder2)
{
	int		i;
	int		ya;
	int		yb;
	int		end;

	i = MAX((int)x.x, 0) - 1;
	end = MIN(W, (int)x.y);
	while (++i < end)
	{
		ya = linear_interpolate(i, vertex(x.x, vborder1.x),
				vertex(x.y, vborder2.x));
		ya = CLAMP(ya, 0, H);
		yb = linear_interpolate(i, vertex(x.x, vborder1.y),
				vertex(x.y, vborder2.y));
		yb = CLAMP(yb, 0, H);
		draw_vline(s, vertex(i, 0), vertex(i, ya - 2), 0xcccccc);
		draw_vline(s, vertex(i, ya - 2), vertex(i, ya - 1), 0x005555);
		draw_vline(s, vertex(i, ya), vertex(i, yb),
			(i == MAX((int)x.x, 0) || i == end - 1) ? 0x005555 : 0x00f0ff);
		draw_vline(s, vertex(i, yb + 1), vertex(i, yb + 2), 0x5555);
		draw_vline(s, vertex(i, yb + 2), vertex(i, H), 0x1f1f1f);
	}
}

void		draw_2d_wall(t_sdl *s, t_wall w)
{
	SDL_SetRenderDrawColor(s->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(s->r, w.v1.x + W/2, w.v1.y + H/2, w.v2.x + W/2, w.v2.y + H/2);
	SDL_RenderPresent(s->r);
}

void		draw_wall(t_sdl *s, t_wall w, t_player p)
{
	int			x1;
	int			x2;
	t_ivertex	vborder1;
	t_ivertex	vborder2;

	w.v1 = player_coords(p, w.v1);
	w.v2 = player_coords(p, w.v2);
	draw_2d_wall(s, w);
	if (w.v1.y <= 0 && w.v2.y <= 0)
		return ;
	if (w.v1.y <= 0 || w.v2.y <= 0)
	{
		clip_wall(&w.v1, &w.v2);
	}
	vborder1 = INIT_IVERTEX(w.ceil - p.z, w.floor - p.z);
	vborder2 = INIT_IVERTEX(w.ceil - p.z, w.floor - p.z);
	x1 = perspective_transform(w.v1, (&vborder1.x), (&vborder1.y));
	x2 = perspective_transform(w.v2, (&vborder2.x), (&vborder2.y));
	if (x1 > x2)
		return ;
	draw_loop(s, vertex((float)x1, (float)x2), IVERTEX_TO_V(vborder1),
			IVERTEX_TO_V(vborder2));
}

void		draw_walls(t_sdl *s, t_sector sector, t_player p)
{
	int		i;

	i = -1;
	while (++i < (int)sector.num_vertices - 1)
	{
		draw_wall(s, INIT_WALL(sector.vertices[i], sector.vertices[i + 1],
					sector.floor, sector.ceil), p);
	}
}

void		draw_sectors(t_sdl *s, t_sector *sectors, t_player p)
{
	SDL_SetRenderDrawColor(s->r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(s->r);
	draw_walls(s, sectors[0], p);
}
