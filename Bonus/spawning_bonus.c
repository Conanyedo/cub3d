/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawning_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:21:09 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 10:40:01 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	spawning(t_cub3d *cub)
{
	cub->posx = cub->parse.x + 0.5;
	cub->posy = cub->parse.y + 0.5;
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
	cub->map[cub->parse.x][cub->parse.y] = '0';
}

void	spawning_ew(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y] == 'E')
	{
		cub->dirx = 0;
		cub->diry = 1;
		cub->planex = 0.66;
		cub->planey = 0;
		cub->parse.spawn = 1;
	}
	else if (cub->map[cub->parse.x][cub->parse.y] == 'W')
	{
		cub->dirx = 0;
		cub->diry = -1;
		cub->planex = -0.66;
		cub->planey = 0;
		cub->parse.spawn = 1;
	}
}

void	spawning_ns(t_cub3d *cub)
{
	if (cub->map[cub->parse.x][cub->parse.y] == 'N')
	{
		cub->dirx = -1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = 0.66;
		cub->parse.spawn = 1;
	}
	else if (cub->map[cub->parse.x][cub->parse.y] == 'S')
	{
		cub->dirx = 1;
		cub->diry = 0;
		cub->planex = 0;
		cub->planey = -0.66;
		cub->parse.spawn = 1;
	}
}

int		character(t_cub3d *cub, int x)
{
	int	found;

	found = 0;
	if (cub->map[x][cub->parse.y] == 'N' ||
			cub->map[x][cub->parse.y] == 'S' ||
			cub->map[x][cub->parse.y] == 'W' ||
			cub->map[x][cub->parse.y] == 'E')
		found = 1;
	else if (!cub->map[x][cub->parse.y] ||
			cub->map[x][cub->parse.y] == '0' ||
			cub->map[x][cub->parse.y] == ' ' ||
			cub->map[x][cub->parse.y] == '1')
		found = 2;
	else if (cub->map[x][cub->parse.y] == '2')
		found = 3;
	return (found);
}

void	ext_error(char *av, char *ext, int *fd)
{
	int		len;

	*fd = open(av, O_RDONLY);
	len = ft_strlen(av) - 4;
	if (*fd < 0 || ft_strncmp(av + len, ext, 4))
		error_msg("Error\nInvalid file");
}
