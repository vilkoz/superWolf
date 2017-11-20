/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 22:29:32 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:43:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h> 
#include "collision.h"
#include "configs.h"

void		detect_sector_change(t_sdl *s, t_player *p, t_vertex d)
{
	int				i;
	t_sector		*sect;
	t_vertex		*v;

	sect = &s->sectors[p->sector];
	v = sect->vertices;
	i = -1;
	while ((unsigned)++i < sect->num_vertices - 1)
		if (sect->neighbors[i] >= 0
		&& INTER_BOX(p->pos, V_ADD(p->pos, d), v[i], v[i+1])
		&& POINT_SIDE(V_ADD(p->pos, d), v[i], v[i+1]) < 0)
		{
			if (s->sectors[p->sector].floor > s->sectors[sect->neighbors[i]].floor)
			{
				p->falling = 1;
				p->ground = 0;
			}
			p->sector = sect->neighbors[i];
			break ;
		}
}

void		vertical_collision(t_sdl *s, t_player *p)
{
	float		next_z;

	if (p->falling)
	{
		next_z = p->z + p->velocity_z;
		if (p->velocity_z < 0
		&& next_z - PLAYER_HEIGHT < s->sectors[p->sector].floor) 
		{
			p->velocity_z = 0;
			p->z = s->sectors[p->sector].floor + PLAYER_HEIGHT;
			p->falling = 0;
			p->ground = 1;
		}
		else if (p->velocity_z > 0 && next_z > s->sectors[p->sector].ceil) 
		{
			p->velocity_z = 0;
			p->z = s->sectors[p->sector].ceil;
		}
		else
			p->z = next_z;
		p->velocity_z = p->velocity_z >= -G ? p->velocity_z - DELTA_G : -G;
	}
	else if (p->z - PLAYER_HEIGHT < s->sectors[p->sector].floor)
			p->z = s->sectors[p->sector].floor + PLAYER_HEIGHT;
}

t_vertex	horisontal_collision(t_sdl *s, t_player *p, t_vertex d)
{
	int				i;
	t_vertex		*v;
	t_vertex		wall;
	t_vertex		tmp;

	v = s->sectors[p->sector].vertices;
	i = -1;
	while ((unsigned)++i < s->sectors[p->sector].num_vertices - 1)
		if (INTER_BOX(p->pos, V_ADD(p->pos, d), v[i], v[i + 1])
		&& POINT_SIDE(V_ADD(p->pos, d), v[i], v[i + 1]) < 0)
		{
			/* TODO: check bumping into top or bottom wall */
			wall = v_sub(v[i], v[i + 1]);
			tmp = d;
			d.x = wall.x * V_DOT(tmp, wall) / V_SQR(wall);
			d.y = wall.y * V_DOT(tmp, wall) / V_SQR(wall);
		}
	return (d);
}
