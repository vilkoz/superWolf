/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 00:25:25 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/20 22:53:46 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTEX_H
# define VERTEX_H

# include <math.h>

typedef struct	s_vertex
{
	float		x;
	float		y;
}				t_vertex;

# define INIT_VERTEX(x, y) ((t_vertex) {(x), (y)})
# define V_DOT(a, b) (a.x * b.x + b.y * a.y)
# define V_SQR(a) (V_DOT(a, a))
# define V_ADD(a, b) (INIT_VERTEX(a.x + b.x, a.y + b.y))
# define V_LEN(a) (sqrt((a).x * (a).x + (a).y * (a).y))
# define V_NORM(a) (INIT_VERTEX(a.x / V_LEN(a), a.y / V_LEN(a)))

t_vertex		vertex(float x, float y);
char			intersect_box(t_vertex a, t_vertex b, t_vertex c, t_vertex d);
t_vertex		v_sub(t_vertex a, t_vertex b);
float			v_cross(t_vertex a, t_vertex b);
char			point_side(t_vertex p, t_vertex l1, t_vertex l2);

#endif
