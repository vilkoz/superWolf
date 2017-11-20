/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 01:05:07 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/20 23:42:08 by vrybalko         ###   ########.fr       */
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
	float			yaw;
	unsigned		sector;
	float			velocity_z;
	char			falling;
	char			ground;
}					t_player;

t_player			player(void);
t_vertex			player_coords(t_player p, t_vertex v);
void				player_rotate(t_player *p, float angle);

#endif
