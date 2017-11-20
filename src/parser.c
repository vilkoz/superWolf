/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:08:05 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/21 00:46:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sector.h"
#include <stdlib.h>

t_sector	*parse(char *path, int *num)
{
	t_sector	*s;
	t_sector	tmp;

	(void)path;
	*num = 2;
	s = (t_sector*)malloc(sizeof(t_sector) * *num);
	tmp = sector(30, 0);
	sector_add_vertex(&tmp, vertex( 10,  10), -1);
	sector_add_vertex(&tmp, vertex(-10,  10), -1);
	sector_add_vertex(&tmp, vertex(-10, -10), -1);
	sector_add_vertex(&tmp, vertex( 10, -10), -1);
	sector_add_vertex(&tmp, vertex( 10,  -5),  1);
	sector_add_vertex(&tmp, vertex( 10,   5), -1);
	sector_add_vertex(&tmp, vertex( 10,  10), -1);
	s[0] = tmp;
	tmp = sector(9, 1);
	sector_add_vertex(&tmp, vertex(40, -10), -1);
	sector_add_vertex(&tmp, vertex(40,  10), -1);
	sector_add_vertex(&tmp, vertex(10,   5),  0);
	sector_add_vertex(&tmp, vertex(10,  -5), -1);
	sector_add_vertex(&tmp, vertex(40, -10), -1);
	s[1] = tmp;
	return (s);
}
