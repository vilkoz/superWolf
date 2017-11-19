/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:08:05 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 19:16:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"
#include <stdlib.h>

t_sector	*parse(char *path)
{
	t_sector	*s;

	(void)path;
	s = (t_sector*)malloc(sizeof(t_sector) * 2);
	s[0].ceil = 10;
	s[0].floor = 0;
	s[0].vertices = (t_vertex*)malloc(sizeof(t_vertex) * 5);
	s[0].neighbors = (int*)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
		s[0].neighbors[i] = -1;
	s[0].neighbors[3] = 1;
	s[0].vertices[0] = vertex(10, 10);
	s[0].vertices[1] = vertex(-10, 10);
	s[0].vertices[2] = vertex(-10, -10);
	s[0].vertices[3] = vertex(10, -10);
	s[0].vertices[4] = vertex(10, 10);
	s[0].num_vertices = 5;
	s[1].ceil = 9.5;
	s[1].floor = 0.5;
	s[1].vertices = (t_vertex*)malloc(sizeof(t_vertex) * 5);
	s[1].neighbors = (int*)malloc(sizeof(int) * 5);
	for (int i = 0; i < 5; i++)
		s[1].neighbors[i] = -1;
	s[1].neighbors[2] = 0;
	s[1].vertices[0] = vertex(40, -10);
	s[1].vertices[1] = vertex(40, 10);
	s[1].vertices[2] = vertex(10, 5);
	s[1].vertices[3] = vertex(10, -5);
	s[1].vertices[4] = vertex(40, -10);
	s[1].num_vertices = 5;
	return (s);
}
