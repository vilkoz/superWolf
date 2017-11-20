/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 00:46:35 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:53:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utility.h"
#include "vertex.h"
#include "configs.h"

inline t_vertex	rotate_vertex(t_vertex v, float cosa, float sina)
{
	t_vertex		n;

	n.x = v.x * sina - v.y * cosa;
	n.y = v.x * cosa + v.y * sina;
	return (n);
}

/*
** returns also to floor and ceil
*/

inline int		perspective_transform(t_vertex v, float *floor, float *ceil,
					t_player p)
{
	t_vertex	scale;
	int			x;

	if (v.y != 0)
	{
		scale.x = (float)HFOV / (float)v.y;
		scale.y = (float)VFOV / (float)v.y;
	}
	else
		scale = vertex(200, 200);
	x = W / 2 - (int)(v.x * scale.x);
	*floor = H / 2 - (int)((*floor + v.y * p.yaw) * scale.y);
	*ceil = H / 2 - (int)((*ceil + v.y * p.yaw) * scale.y);
	return (x);
}

inline t_vertex	intersect_lines(t_vertex p1, t_vertex p2, t_vertex p3,
						t_vertex p4)
{
	t_vertex		v;

	v.x = v_cross(vertex(v_cross(p1, p2), p1.x - p2.x),
			vertex(v_cross(p3, p4), p3.x - p4.x));
	v.x /= v_cross(v_sub(p1, p2), v_sub(p3, p4));
	v.y = v_cross(vertex(v_cross(p1, p2), p1.y - p2.y),
			vertex(v_cross(p3, p4), p3.y - p4.y));
	v.y /= v_cross(v_sub(p1, p2), v_sub(p3, p4));
	return (v);
}

inline void		clip_wall(t_vertex *v1, t_vertex *v2)
{
	t_vertex	i1;
	t_vertex	i2;

	i1 = intersect_lines(*v1, *v2, vertex(-NEAR_X, NEAR_Z),
			vertex(-FAR_X, FAR_Z));
	i2 = intersect_lines(*v1, *v2, vertex(NEAR_X, NEAR_Z),
			vertex(FAR_X, FAR_Z));
	if (v1->y < NEAR_Z)
		*v1 = (i1.y > 0) ? i1 : i2;
	if (v2->y < NEAR_Z)
		*v2 = (i1.y > 0) ? i1 : i2;
}

inline int		linear_interpolate(int x, t_vertex p1, t_vertex p2)
{
	if (p2.x - p1.x == 0)
		return (H);
	x = CLAMP(x, (int)p1.x, (int)p2.x);
	return ((int)((((float)x - p1.x) / (p2.x - p1.x)) * (p2.y - p1.y) + p1.y));
}
