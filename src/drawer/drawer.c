/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 12:51:11 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 01:02:44 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl.h"
#include "utility.h"
#include "vertex.h"
#include "player.h"
#include "configs.h"
#include "drawer.h"

void		draw_vline(t_sdl *s, t_vertex v1, t_vertex v2, unsigned color)
{
	SDL_Rect		rect;

	rect.x = (int)MIN(v1.x, v2.x);
	rect.y = (int)v1.y;
	rect.w = 1;
	rect.h = (int)v2.y - rect.y;
	SDL_FillRect(s->surface, &rect, color);
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
	t_ivertex	x;
	t_ivertex	y;

	x.x = MAX((int)w.x.x, now.xstart) - 1;
	x.y = MIN(now.xend, (int)w.x.y);
	if (w.next >= 0 && x.x + 1 <= x.y)
		queue_push(&s->queue, (void*)&INIT_ITEM(w.next, (x.x + 1), x.y));
	while (++x.x < x.y)
	{
		y.x = linear_interpolate(x.x, vertex(w.x.x, w.v1.x),
				vertex(w.x.y, w.v2.x));
		y.x = CLAMP(y.x, s->ystart[x.x], s->yend[x.x]);
		y.y = linear_interpolate(x.x, vertex(w.x.x, w.v1.y),
				vertex(w.x.y, w.v2.y));
		y.y = CLAMP(y.y, s->ystart[x.x], s->yend[x.x]);
		draw_vline(s, vertex(x.x, s->ystart[x.x]), vertex(x.x, y.x - 2), CCEIL);
		draw_vline(s, vertex(x.x, y.x - 2), vertex(x.x, y.x - 1), CBORD);
		draw_vline(s, vertex(x.x, y.y + 1), vertex(x.x, y.y + 2), CBORD);
		draw_vline(s, vertex(x.x, y.y + 2), vertex(x.x, s->yend[x.x]), CFLOR);
		if (w.next == -1)
			draw_vline(s, vertex(x.x, y.x), vertex(x.x, y.y),
				(x.x == MAX((int)w.x.x, 0) || x.x == x.y - 1) ? CBORD : CWALL);
		else
			draw_neighbor(s, w, x.x, INIT_IVERTEX(y.x, y.y));
	}
}

void		draw_wall(t_sdl *s, t_wall w, t_player p, t_item now)
{
	t_ivertex	x;
	t_pwall		borders;

	w.v1 = player_coords(p, w.v1);
	w.v2 = player_coords(p, w.v2);
	if (w.v1.y <= 0 && w.v2.y <= 0)
		return ;
	if (w.v1.y <= 0 || w.v2.y <= 0)
		clip_wall(&w.v1, &w.v2);
	borders.v1 = INIT_VERTEX(w.ceil - p.z, w.floor - p.z);
	borders.v2 = INIT_VERTEX(w.ceil - p.z, w.floor - p.z);
	x.x = perspective_transform(w.v1, (&borders.v1.x), (&borders.v1.y), p);
	x.y = perspective_transform(w.v2, (&borders.v2.x), (&borders.v2.y), p);
	if (x.x > x.y || x.y < now.xstart || x.x > now.xend)
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

	queue_init(&s->queue, MAX_QUEUE, sizeof(t_item));
	queue_push(&s->queue, (void*)&INIT_ITEM(p.sector, 0, W - 1));
	ft_bzero((void*)rendered, s->num_sectors * sizeof(int));
	i = -1;
	ft_bzero((void*)s->ystart, W * sizeof(int));
	while (++i < W)
		s->yend[i] = H - 1;
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
