/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:21:09 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/18 12:28:42 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spawning(t_cub3d *cub)
{
	if (!cub->map[cub->parse.x][cub->parse.y + 1] ||
			cub->map[cub->parse.x - 1][cub->parse.y] == ' ' ||
			cub->map[cub->parse.x - 1][cub->parse.y] == '\0')
		error_msg_free("ERROR\nSpawning position invalid", cub);
	if (cub->map[cub->parse.x][cub->parse.y] == 'N' ||
			cub->map[cub->parse.x][cub->parse.y] == 'S')
		spawning_ns(cub);
	else if (cub->map[cub->parse.x][cub->parse.y] == 'E' ||
		cub->map[cub->parse.x][cub->parse.y] == 'W')
		spawning_ew(cub);
}

void	spawning_ew(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y] == 'E')
	{
		cub->posx = cub->parse.x;
		cub->posy = cub->parse.y;
		cub->dirx = 0;
		cub->diry = 1;
		cub->planex = 0.66;
		cub->planey = 0;
		cub->parse.spawn = 1;
	}
	else if (cub->map[cub->parse.x][cub->parse.y] == 'W')
	{
		cub->posx = cub->parse.x;
		cub->posy = cub->parse.y;
		cub->dirx = 0;
		cub->diry = -1;
		cub->planex = -0.66;
		cub->planey = 0;
		cub->parse.spawn = 1;
	}
	cub->map[cub->parse.x][cub->parse.y] = '0';
}

void	spawning_ns(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y] == 'N')
	{
		cub->posx = cub->parse.x;
		cub->posy = cub->parse.y;
		cub->dirx = -1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = 0.66;
		cub->parse.spawn = 1;
	}
	else if (cub->map[cub->parse.x][cub->parse.y] == 'S')
	{
		cub->posx = cub->parse.x;
		cub->posy = cub->parse.y;
		cub->dirx = 1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = -0.66;
		cub->parse.spawn = 1;
	}
	cub->map[cub->parse.x][cub->parse.y] = '0';
}

int		character(t_cub3d *cub)
{
	int	found;

	found = 0;
	if (cub->map[cub->parse.x][cub->parse.y] == 'N' ||
			cub->map[cub->parse.x][cub->parse.y] == 'S' ||
			cub->map[cub->parse.x][cub->parse.y] == 'W' ||
			cub->map[cub->parse.x][cub->parse.y] == 'E')
		found = 1;
	else if (!cub->map[cub->parse.x][cub->parse.y] ||
			cub->map[cub->parse.x][cub->parse.y] == '0' ||
			cub->map[cub->parse.x][cub->parse.y] == ' ' ||
			cub->map[cub->parse.x][cub->parse.y] == '1')
		found = 2;
	return (found);
}
