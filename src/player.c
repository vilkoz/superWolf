/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:04:55 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:16:09 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h> 
#include "player.h"
#include "utility.h"
#include "sdl.h"
#include "configs.h"
#include "collision.h"

t_player			player(void)
{
	t_player		p;

	p.pos = vertex(0, 0);
	p.angle = 0;
	p.sin = sinf(p.angle);
	p.cos = cosf(p.angle);
	p.z = PLAYER_HEIGHT;
	p.sector = 0;
	p.yaw = 1;
	p.velocity_z = 0;
	p.falling = 0;
	p.ground = 1;
	return (p);
}

inline t_vertex		player_coords(t_player p, t_vertex v)
{
	t_vertex	n;

	n = v_sub(v, p.pos);
	n = rotate_vertex(n, p.cos, p.sin);
	return (rotate_vertex(v_sub(v, p.pos), p.cos, p.sin));
}

inline void			player_rotate(t_player *p, float angle)
{
	p->angle += angle;
	p->sin = sinf(p->angle);
	p->cos = cosf(p->angle);
}

inline void			player_move(t_sdl *s, t_player *p, float amp)
{
	t_vertex		d;

	d = INIT_VERTEX(p->cos * 0.2 * amp, p->sin * 0.2 * amp);
	detect_sector_change(s, p, d);
	d = horisontal_collision(s, p, d);
	p->pos = V_ADD(p->pos, d);
}

inline void			player_jump(t_player *p)
{
	if (!p->ground)
		return ;
	p->velocity_z = JUMP_G;
	p->falling = 1;
	p->ground = 0;
}
