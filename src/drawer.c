/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 12:51:11 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 19:26:59 by vrybalko         ###   ########.fr       */
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
	rect.y = (int)v1.y;
	rect.w = 1;
	rect.h = (int)v2.y - rect.y;
	SDL_FillRect(s->surface, &rect, color);
}

void		draw_neighbor(t_sdl *s, t_pwall w, int i, t_ivertex v)
{
	int		ya;
	int		yb;


	ya = linear_interpolate(i, vertex(w.x.x, w.n1.x),
			vertex(w.x.y, w.n2.x));
	ya = CLAMP(ya, 0, H);
	yb = linear_interpolate(i, vertex(w.x.x, w.n1.y),
			vertex(w.x.y, w.n2.y));
	yb = CLAMP(yb, 0, H);
	draw_vline(s, vertex(i, v.x), vertex(i, ya - 1), 0x097df9);
	draw_vline(s, vertex(i, ya - 1), vertex(i, ya), 0xffffff);
	s->ystart[i] = CLAMP(MAX(ya, v.x), s->ystart[i], H - 1);
	draw_vline(s, vertex(i, yb), vertex(i, yb + 1), 0xffffff);
	draw_vline(s, vertex(i, yb + 1), vertex(i, v.y), 0x097df9);
	s->yend[i] = CLAMP(MIN(yb, v.y), 0, s->yend[i]);
}

/*
** typedef struct	s_pwall
** {
** 	t_vertex	x; // own horisontal borders
** 	t_vertex	v1; // own borders
** 	t_vertex	v2;
** 	t_vertex	n1; // neighbors' borders
** 	t_vertex	n2;
** 	int			next; //neighbors' sector num, -1 if no
** }				t_pwall;
*/

void		draw_loop(t_sdl *s, t_pwall w, t_item now)
{
	int		i;
	int		ya;
	int		yb;
	int		end;

	i = MAX((int)w.x.x, now.xstart) - 1;
	end = MIN(now.xend, (int)w.x.y);
	if (w.next >= 0 && i + 1 <= end)
		queue_push(&s->queue, (void*)&INIT_ITEM(w.next, (i + 1), end));
	while (++i < end)
	{
		ya = linear_interpolate(i, vertex(w.x.x, w.v1.x),
				vertex(w.x.y, w.v2.x));
		ya = CLAMP(ya, s->ystart[i], s->yend[i]);
		yb = linear_interpolate(i, vertex(w.x.x, w.v1.y),
				vertex(w.x.y, w.v2.y));
		yb = CLAMP(yb, s->ystart[i], s->yend[i]);
		draw_vline(s, vertex(i, s->ystart[i]), vertex(i, ya - 2), 0xcccccc);
		draw_vline(s, vertex(i, ya - 2), vertex(i, ya - 1), 0x005555);
		draw_vline(s, vertex(i, yb + 1), vertex(i, yb + 2), 0x5555);
		draw_vline(s, vertex(i, yb + 2), vertex(i, s->yend[i]), 0x1f1f1f);
		if (w.next == -1)
			draw_vline(s, vertex(i, ya), vertex(i, yb),
				(i == MAX((int)w.x.x, 0) || i == end - 1) ? 0x5555 : 0xf0ff);
		else
			draw_neighbor(s, w, i, INIT_IVERTEX(ya, yb));
	}
}

void		draw_2d_wall(t_sdl *s, t_wall w)
{
	SDL_SetRenderDrawColor(s->r, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(s->r, w.v1.x + W/2, w.v1.y + H/2, w.v2.x + W/2, w.v2.y + H/2);
	SDL_RenderPresent(s->r);
}

void		init_neighbor(t_ipwall *borders, t_wall w, t_sector s, t_player p)
{
	borders->n1 = INIT_IVERTEX(s.ceil - p.z, s.floor - p.z);
	borders->n2 = INIT_IVERTEX(s.ceil - p.z, s.floor - p.z);
	perspective_transform(w.v1, &borders->n1.x, &borders->n1.y);
	perspective_transform(w.v2, &borders->n2.x, &borders->n2.y);
}

void		draw_wall(t_sdl *s, t_wall w, t_player p, t_item now)
{
	t_ivertex	x;
	t_ipwall	borders;

	w.v1 = player_coords(p, w.v1);
	w.v2 = player_coords(p, w.v2);
	draw_2d_wall(s, w);
	if (w.v1.y <= 0 && w.v2.y <= 0)
		return ;
	if (w.v1.y <= 0 || w.v2.y <= 0)
		clip_wall(&w.v1, &w.v2);
	borders.v1 = INIT_IVERTEX(w.ceil - p.z, w.floor - p.z);
	borders.v2 = INIT_IVERTEX(w.ceil - p.z, w.floor - p.z);
	x.x = perspective_transform(w.v1, (&borders.v1.x), (&borders.v1.y));
	x.y = perspective_transform(w.v2, (&borders.v2.x), (&borders.v2.y));
	if (x.x > x.y)
		return ;
	if (w.next >= 0)
		init_neighbor(&borders, w, s->sectors[w.next], p);
	draw_loop(s, IPWALL_TO_P(borders, x, w.next), now);
}

void		draw_walls(t_sdl *s, t_sector sector, t_player p, t_item now)
{
	int		i;

	i = -1;
	while (++i < (int)sector.num_vertices - 1)
	{
		draw_wall(s, INIT_WALL(sector.vertices[i], sector.vertices[i + 1],
					sector.floor, sector.ceil, sector.neighbors[i]), p, now);
	}
}

void		draw_sectors(t_sdl *s, t_sector *sectors, t_player p)
{
	t_item		*now;
	int			i;
	int			rendered[2];

	SDL_SetRenderDrawColor(s->r, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(s->r);
	queue_init(&s->queue, MAX_QUEUE, sizeof(t_item));
	queue_push(&s->queue, (void*)&INIT_ITEM(p.sector, 0, W - 1));
	ft_bzero((void*)rendered, 2 * sizeof(int));
	i = -1;
	while (++i < W)
	{
		s->ystart[i] = 0;
		s->yend[i] = H - 1;
	}
	while (23)
	{
		if ((now = (t_item*)queue_pop(&s->queue)) == NULL)
			break ;
		if (rendered[now->num] & (MAX_QUEUE + 1))
			break ;
		draw_walls(s, sectors[now->num], p, *now);
		rendered[now->num]++;
		ft_memdel((void**)&now);
	}
}
