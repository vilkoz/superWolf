/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 00:25:25 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 21:32:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

typedef struct	s_vertex
{
	float		x;
	float		y;
}				t_vertex;

# define INIT_VERTEX(x, y) ((t_vertex) {(x), (y)})
# define V_ADD(a, b) (INIT_VERTEX(a.x + b.x, a.y + b.y))

t_vertex		vertex(float x, float y);
char			intersect_box(t_vertex a, t_vertex b, t_vertex c, t_vertex d);
t_vertex		v_sub(t_vertex a, t_vertex b);
float			v_cross(t_vertex a, t_vertex b);
char			point_side(t_vertex p, t_vertex l1, t_vertex l2);

#endif
