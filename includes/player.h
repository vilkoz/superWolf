/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:05:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/18 12:53:35 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "vertex.h"

typedef struct		s_player
{
	t_vertex		pos;
	float			angle;
	float			cos;
	float			sin;
	float			z;
	unsigned		sector;
}					t_player;

t_player			player(void);
t_vertex			player_coords(t_player p, t_vertex v);
void				player_rotate(t_player *p, float angle);
void				player_move(t_player *p, float amp);

#endif
