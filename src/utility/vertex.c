/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 00:26:40 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 02:19:16 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vertex.h"
#include "utility.h"

inline t_vertex	vertex(float x, float y)
{
	t_vertex	n;

	n.x = x;
	n.y = y;
	return (n);
}

inline char		intersect_box(t_vertex a, t_vertex b, t_vertex c, t_vertex d)
{
	return (OVERLAP(a.x, a.y, c.x, c.y) && OVERLAP(b.x, b.y, d.x, d.y));
}

inline t_vertex	v_sub(t_vertex a, t_vertex b)
{
	return (vertex(a.x - b.x, a.y - b.y));
}

inline float	v_cross(t_vertex a, t_vertex b)
{
	return (a.x * b.y - a.y * b.x);
}

inline char		point_side(t_vertex p, t_vertex l1, t_vertex l2)
{
	float a;

	a = v_cross(v_sub(l2, l1), v_sub(p, l1));
	if (a < 0)
		return (-1);
	else if (a < 0.0001)
		return (0);
	return (1);
}
