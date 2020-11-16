/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:21:09 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 12:24:13 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawning(t_cub3d *cub)
{
	if (!cub->map[cub->parse.X][cub->parse.Y + 1] ||
			cub->map[cub->parse.X - 1][cub->parse.Y] == ' ' ||
			cub->map[cub->parse.X - 1][cub->parse.Y] == '\0')
		error_msg_free("ERROR\nSpawning position invalid", cub);
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'S')
		spawning_ns(cub);
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'E' ||
		cub->map[cub->parse.X][cub->parse.Y] == 'W')
		spawning_ew(cub);
}

void	spawning_ew(t_cub3d *cub)
{
	if (cub->map[cub->parse.X][cub->parse.Y] == 'E')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 0;
		cub->dirY = 1;
		cub->planeX = 0.66;
		cub->planeY = 0;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'W')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 0;
		cub->dirY = -1;
		cub->planeX = -0.66;
		cub->planeY = 0;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
}

void	spawning_ns(t_cub3d *cub)
{
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = -1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = 0.66;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'S')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = -0.66;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
}

int		character(t_cub3d *cub)
{
	int	found;

	found = 0;
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'S' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'W' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'E')
		found = 1;
	else if (!cub->map[cub->parse.X][cub->parse.Y] ||
			cub->map[cub->parse.X][cub->parse.Y] == '0' ||
			cub->map[cub->parse.X][cub->parse.Y] == ' ' ||
			cub->map[cub->parse.X][cub->parse.Y] == '1')
		found = 2;
	return (found);
}
